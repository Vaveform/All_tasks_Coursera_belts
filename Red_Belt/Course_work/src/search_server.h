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
using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
  vector<pair<size_t, size_t>> Lookup(const string& word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

  size_t GetNumberDocuments() const {
	  return docs.size();
  }

private:
  map<string, vector<pair<size_t, size_t>>> index;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
