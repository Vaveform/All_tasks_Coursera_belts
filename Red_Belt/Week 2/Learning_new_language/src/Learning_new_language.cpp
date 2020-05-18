#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <set>

#include "profile.h"

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
	int newWords = 0;
    for (const auto& word : words) {
        auto cmp = dict.insert(word);
        if(cmp.second == true){
        	newWords++;
        }
    }
    return newWords;
  }

  vector<string> KnownWords() {
	vector<string> result(dict.begin(), dict.end());
    return result;
  }
};

class Learner2 {
 private:
  vector<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (find(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
};

int main()
{
	vector<string> RussianWords(10000);
	for(auto& elem: RussianWords){
		string cmp;
		for(int i = 0; i < 5; i++){
			int co = rand() % (90 - 65 + 1) + 65;
			cmp.push_back(char(co));
		}
		elem = cmp;
	}
	Learner Russian;
	Learner2 Rus;
	{
		LOG_DURATION("Set learn");
	    int newWords = Russian.Learn(RussianWords);
	}
	{
		LOG_DURATION("Set knownWords");
	    auto KnownWords = Russian.KnownWords();
	}
	{
		LOG_DURATION("Vector learn");
		int newWords = Rus.Learn(RussianWords);
	}
	{
		LOG_DURATION("Vector knownWords");
		auto KnownWords = Rus.KnownWords();
	}
	return 0;
}
