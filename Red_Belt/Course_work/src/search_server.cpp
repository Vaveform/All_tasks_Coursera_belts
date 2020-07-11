#include "search_server.h"
#include "iterator_range.h"
#include "Timer.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <functional>
#include <future>


vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;
  for (string current_document; getline(document_input, current_document); ) {
	new_index.Add(move(current_document));
  }

  {
	  auto access_to_swap = this->index.GetAccess();
	  swap(access_to_swap.ref_to_value, new_index);
  }
}

void SearchServer::AddQueriesStreamOneThread(istream& query_input, ostream& search_results_output){
	size_t Base_Size = 0;
	{
		auto access_to_get_size = index.GetAccess();
		Base_Size = access_to_get_size.ref_to_value.GetNumberDocuments();
	}

	  vector<pair<size_t, size_t>> doc_id(Base_Size);
	  for (string current_query; getline(query_input, current_query); ) {
		const auto words = SplitIntoWords(current_query);
		std::fill_n(doc_id.begin(), doc_id.size(), make_pair(Base_Size, 0));

		for (const auto& word : words) {
			vector<pair<size_t, size_t>> lookuped;
			{
				auto acces_to_get_vec = index.GetAccess();
				lookuped = acces_to_get_vec.ref_to_value.Lookup(word);
			}
		  for (const auto& pair : lookuped) {
			doc_id[pair.first].first = pair.first;
			doc_id[pair.first].second += pair.second;
		  }
		}
		vector<pair<size_t, size_t>> resulting_search;
		copy_if(doc_id.begin(), doc_id.end(), back_inserter(resulting_search), [&Base_Size](pair<size_t, size_t>& val){
			return val.first != Base_Size && val.second != 0;
		});

		auto Range = Head(resulting_search, 5);
		partial_sort(
				Range.begin(),
				Range.end(),
				resulting_search.end(),
				[](pair<size_t, size_t>& lhs, pair<size_t, size_t>& rhs) {
				            int64_t lhs_docid = lhs.first;
				            auto lhs_hit_count = lhs.second;
				            int64_t rhs_docid = rhs.first;
				            auto rhs_hit_count = rhs.second;
				            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
				          }
				        );

		search_results_output << current_query << ':';
		for (auto& [docid, hitcount] : Range) {
			search_results_output << " {"
					<< "docid: " << docid << ", "
					<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	  }
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
//	async_threads.push_back(async(launch::async, &SearchServer::AddQueriesStreamOneThread, this, ref(query_input), ref(search_results_output)));
	AddQueriesStreamOneThread(query_input, search_results_output);
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);
  vector<string> words = SplitIntoWords(document);
  const size_t docid = docs.size() - 1;
  for (const auto& word : words) {
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

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string& word) const {
  auto it = index.find(word);
  if (it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
