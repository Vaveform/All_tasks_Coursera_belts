#include "search_server.h"
#include "iterator_range.h"
#include "Timer.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <functional>
#include <future>
#include <string_view>


vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBaseOneThread(document_input);
}

void SearchServer::UpdateDocumentBaseOneThread(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
	new_index.Add(move(current_document));
  }

  {
	  lock_guard<mutex> lock_index(lock_inverted_index);
	  swap(index, new_index);
  }
}

void SearchServer::UpdateDocumentBase(istream& document_input){
	async_update_base.push_back(async(launch::async, &SearchServer::UpdateDocumentBaseOneThread, this, ref(document_input)));
}


void SearchServer::AddQueriesStreamOneThread(istream& query_input, ostream& search_results_output){
	int Base_Size = 0;
	{
		lock_guard<mutex> lock_index(lock_inverted_index);
		Base_Size = index.GetNumberDocuments();
	}

	  vector<pair<size_t, int>> doc_id(Base_Size, make_pair(0, -Base_Size));
	  for (string current_query; getline(query_input, current_query); ) {
		const auto words = SplitIntoWords(current_query);

		for (const auto& word : words) {
			for (const auto& pair : index.Lookup(word)) {
				doc_id[pair.first].first += pair.second;
				doc_id[pair.first].second = -1 * pair.first;
			}
		}

		vector<pair<size_t, int>> resulting_search;
		for(pair<size_t, int>& pair : doc_id){
			if(pair.second != -1 * Base_Size && pair.first != 0){
				resulting_search.push_back(pair);
				pair.second = -1 * Base_Size;
				pair.first = 0;
			}
		}

		auto Range = Head(resulting_search, 5);
		partial_sort(
				Range.begin(),
				Range.end(),
				resulting_search.end(),
				[](const pair<size_t, int>& lhs,const pair<size_t, int>& rhs) {
				            return lhs > rhs;
				          }
				        );

		search_results_output << current_query << ':';
		for (auto& [hitcount, docid] : Range) {
			search_results_output << " {"
					<< "docid: " << -1 * docid << ", "
					<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	  }
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
	async_queries.push_back(async(launch::async, &SearchServer::AddQueriesStreamOneThread, this, ref(query_input), ref(search_results_output)));
}

void InvertedIndex::Add(const string& document) {
  //  docs.push_back(document);
  size++;
  const size_t docid = size - 1;
  for (const auto& word : SplitIntoWords(document)) {
	  auto iterator_to_insert = index.find(word);
	  if(iterator_to_insert == index.end()){
		  index[word].push_back(make_pair(docid, 1));
	  }
	  else{
		  if(iterator_to_insert->second.back().first != docid){
			  iterator_to_insert->second.push_back(make_pair(docid, 1));
		  }
		  else{
			  iterator_to_insert->second.back().second += 1;
		  }
	  }
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
  auto it = index.find(word);
  if (it != index.end()) {
	return it->second;
  } else {
	return null_reference;
  }
//	return index.find(word);
}
