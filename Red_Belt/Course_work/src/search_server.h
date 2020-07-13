#pragma once

#include "Timer.h"

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
#include <mutex>
#include <future>
#include <unordered_map>
using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
  const vector<pair<size_t, size_t>>& Lookup(const string& word) const;

  size_t GetNumberDocuments() const {
	  return size;
  }
private:
  unordered_map<string, vector<pair<size_t, size_t>>> index;
  vector<pair<size_t, size_t>> null_reference;
  size_t size = 0;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBaseOneThread(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStreamOneThread(istream& query_input, ostream& search_results_output);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
private:
  InvertedIndex index;
  mutex lock_inverted_index;
  vector<future<void>> async_queries;
  vector<future<void>> async_update_base;
};