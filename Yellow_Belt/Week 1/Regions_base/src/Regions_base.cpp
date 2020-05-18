#include <iostream>
#include <tuple>
#include <cstdint>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

auto GetRank(const Region& region){
	return tie(region.std_name, region.parent_std_name,
			region.names, region.population);
}

bool operator==(const Region& lhs, const Region& rhs)
{
	return GetRank(lhs) == GetRank(rhs);
}

bool operator<(const Region& lhs, const Region& rhs)
{
	return GetRank(lhs) < GetRank(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
	if(regions.size() == 0){
		return 0;
	}
	else{
		map<Region, int> repeats;
		int max_frequency = 0;
		for(auto const& elem: regions)
		{
			repeats[elem]+=1;
		}
		for(auto const& item:repeats){
			if(item.second > max_frequency){
				max_frequency = item.second;
			}
		}
		return max_frequency;
	}
}

int main() {
	cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "zsdfMoskau"}, {Lang::FR, "zsdfMoscou"}, {Lang::IT, "azseMosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
		          "Moscow",
		          "Russia",
		          {{Lang::DE, "adMoskauqw"}, {Lang::FR, "adMoscou"}, {Lang::IT, "awMoscaqwd"}},
		          119
		      },
			  {
			 	          "Moscow",
			 	          "Russia",
			 	          {{Lang::DE, "adMoskau"}, {Lang::FR, "daMoscouqwd"}, {Lang::IT, "Mosca"}},
			 	          389
			 	      },
	  }) << endl;

	  cout << FindMaxRepetitionCount({
	      {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Russia",
	          "Eurasia",
	          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Toulouse",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          89
	      }, {
	          "Moscow",
	          "Russia",
	          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
	          31
	      },
	  }) << endl;
	return 0;
}
