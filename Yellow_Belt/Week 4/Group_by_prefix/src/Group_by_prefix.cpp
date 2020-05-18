#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix)
{
	string tmp_string;
	tmp_string.push_back(prefix);
	auto result = equal_range(range_begin, range_end, tmp_string, [tmp_string](auto str1, auto str2){
		return (str2.substr(0, tmp_string.size()) > str1.substr(0, tmp_string.size()));
	});
	return result;
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix)
{
	auto result = equal_range(range_begin, range_end, prefix, [prefix](auto str1, auto str2){
		return (str2.substr(0, prefix.size()) > str1.substr(0, prefix.size()));
	});
	return result;
}

int main()
{
	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

	  const auto mo_result =
	      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	  for (auto it = mo_result.first; it != mo_result.second; ++it) {
	    cout << *it << " ";
	  }
	  cout << endl;

	  const auto mt_result =
	      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	  cout << (mt_result.first - begin(sorted_strings)) << " " <<
	      (mt_result.second - begin(sorted_strings)) << endl;

	  const auto na_result =
	      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	  cout << (na_result.first - begin(sorted_strings)) << " " <<
	      (na_result.second - begin(sorted_strings)) << endl;


	return 0;
}
