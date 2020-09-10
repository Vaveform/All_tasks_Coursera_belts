#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <unordered_set>
#include "test_runner.h"

using namespace std;

bool IsSubDomain(string_view domain, string_view Sub) {
	size_t pos_begin = domain.find(Sub);
	size_t pos_end = pos_begin + Sub.size();
	if(pos_end == domain.size() && pos_begin == 0){
		return true;
	}
	if(pos_begin == 0 && domain[pos_end] == '.'){
		return true;
	}
	return false;
}

vector<string> ReadBannedDomains() {
  size_t count;
  cin >> count;

  vector<string> domains;
  for (size_t i = 0; i < count; ++i) {
    string domain;
    cin >> domain;
    reverse(domain.begin(), domain.end());
    domains.push_back(domain);
  }
  sort(domains.begin(), domains.end());
  auto it = unique(domains.begin(), domains.end(), [](const string& first, const string& second){
      return IsSubDomain(first, second) || IsSubDomain(second, first);
  });
  domains.erase(it,domains.end());
  return domains;
}


vector<string> ReadDomainsToCheck() {
  size_t count;
  cin >> count;

  vector<string> domains;
  for (size_t i = 0; i < count; ++i) {
    string domain;
    cin >> domain;
    reverse(domain.begin(), domain.end());
    domains.push_back(domain);
  }
  return domains;
}

bool isProhibitedDomain(const string& domain, const vector<string>& sorted_sub_domains){
	size_t i = 0;
	while(i != domain.npos){
		i = domain.find('.', i + 1);
		bool result = binary_search(sorted_sub_domains.begin(), sorted_sub_domains.end(), domain.substr(0, i));
		if(result == true){
			return result;
		}
	}
	return false;
}

void ReverseWords(vector<string>& words){
	for(string& element : words){
		reverse(element.begin(), element.end());
	}
}

void Test_5a(){
	vector<string> Sub_domains = {"com"};
	vector<string> domains_to_check = {"com.ru",
	"ru.com.en", "ru.com"};
	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[2], Sub_domains[0]), true);
}

void Test_5b(){
	vector<string> Sub_domains = {"ya.ya",
	"ya.ru", "ya.com"};
	vector<string> domains_to_check = {"haya.ya",
	"teya.ru", "suya.com", "ha.ya.ya", "te.ya.ru",
	"su.ya.com", "ya.ya", "ya.ru", "ya.com"};
	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[2], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[2], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[2], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[3], Sub_domains[0]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[3], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[3], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[4], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[4], Sub_domains[1]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[4], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[5], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[5], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[5], Sub_domains[2]), true);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[6], Sub_domains[0]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[6], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[6], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[7], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[7], Sub_domains[1]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[7], Sub_domains[2]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[8], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[8], Sub_domains[1]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[8], Sub_domains[2]), true);
}

void Test_6(){
	vector<string> Sub_domains = {"m", "cool"};
	vector<string> domains_to_check = {"m.vk.com", "cool.site.ru"};
	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[1]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[1]), false);

	Sub_domains = {"m.cool", "cool.site"};
	domains_to_check = {"m.cool.vk.com", "cool.site.ru"};
	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[1]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[1]), false);

	Sub_domains = {"m.vk.com", "site.ru"};
	domains_to_check = {"m.vk.com", "cool.site.ru"};
	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[1]), false);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[0]), false);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[1], Sub_domains[1]), true);
}

void Test_7(){
	vector<string> Sub_domains = {"b.c", "a.b.c"};
	vector<string> domains_to_check = {"d.b.c"};

	ReverseWords(Sub_domains);
	ReverseWords(domains_to_check);

	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[0]), true);
	ASSERT_EQUAL(IsSubDomain(domains_to_check[0], Sub_domains[1]), false);
}

int main() {
	TestRunner tr;
	tr.RunTest(Test_5a, "Test_5a runned");
	tr.RunTest(Test_5b, "Test_5b runned");
	tr.RunTest(Test_6, "Test_6 runned");
	tr.RunTest(Test_7, "Test_7 runned");
	const vector<string> Sub_domains = ReadBannedDomains();
	const vector<string> domains_to_check = ReadDomainsToCheck();
	for(const auto& domain : domains_to_check){
	  if(isProhibitedDomain(domain, Sub_domains)){
		  cout << "Bad" << endl;
	  }
	  else{
		  cout << "Good" << endl;
	  }
	}
	return 0;
}
