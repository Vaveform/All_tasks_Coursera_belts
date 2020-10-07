#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

template <typename It>
class Range {
public:
  Range(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

vector<string_view> Split(string_view s, string_view delimiter = " ") {
  vector<string_view> parts;
  if (s.empty()) {
    return parts;
  }
  while (true) {
    const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
    parts.push_back(lhs);
    if (!rhs_opt) {
      break;
    }
    s = *rhs_opt;
  }
  return parts;
}


class Domain {
public:
  explicit Domain(string_view text) {
    vector<string_view> parts = Split(text, ".");
    parts_reversed_.assign(rbegin(parts), rend(parts));
  }

  size_t GetPartCount() const {
    return parts_reversed_.size();
  }

  auto GetParts() const {
    return Range(rbegin(parts_reversed_), rend(parts_reversed_));
  }
  auto GetReversedParts() const {
    return Range(begin(parts_reversed_), end(parts_reversed_));
  }

  bool operator==(const Domain& other) const {
    return parts_reversed_ == other.parts_reversed_;
  }

private:
  vector<string> parts_reversed_;
};

ostream& operator<<(ostream& stream, const Domain& domain) {
  bool first = true;
  for (const string_view part : domain.GetParts()) {
    if (!first) {
      stream << '.';
    } else {
      first = false;
    }
    stream << part;
  }
  return stream;
}

// domain is subdomain of itself
bool IsSubdomain(const Domain& subdomain, const Domain& domain) {
  const auto subdomain_reversed_parts = subdomain.GetReversedParts();
  const auto domain_reversed_parts = domain.GetReversedParts();
  return
      subdomain.GetPartCount() >= domain.GetPartCount()
      && equal(begin(domain_reversed_parts), end(domain_reversed_parts),
               begin(subdomain_reversed_parts));
}

bool IsSubOrSuperDomain(const Domain& lhs, const Domain& rhs) {
  return lhs.GetPartCount() >= rhs.GetPartCount()
         ? IsSubdomain(lhs, rhs)
         : IsSubdomain(rhs, lhs);
}


class DomainChecker {
public:
  template <typename InputIt>
  DomainChecker(InputIt domains_begin, InputIt domains_end) {
    sorted_domains_.reserve(distance(domains_begin, domains_end));
    for (const Domain& domain : Range(domains_begin, domains_end)) {
      sorted_domains_.push_back(&domain);
    }
    sort(begin(sorted_domains_), end(sorted_domains_), IsDomainLess);
    sorted_domains_ = AbsorbSubdomains(move(sorted_domains_));
  }

  // Check if candidate is subdomain of some domain
  bool IsSubdomain(const Domain& candidate) const {
    const auto it = upper_bound(
        begin(sorted_domains_), end(sorted_domains_),
        &candidate, IsDomainLess);
    if (it == begin(sorted_domains_)) {
      return false;
    }
    return ::IsSubdomain(candidate, **prev(it));
  }

private:
  vector<const Domain*> sorted_domains_;

  static bool IsDomainLess(const Domain* lhs, const Domain* rhs) {
    const auto lhs_reversed_parts = lhs->GetReversedParts();
    const auto rhs_reversed_parts = rhs->GetReversedParts();
    return lexicographical_compare(
      begin(lhs_reversed_parts), end(lhs_reversed_parts),
      begin(rhs_reversed_parts), end(rhs_reversed_parts)
    );
  }

  static vector<const Domain*> AbsorbSubdomains(vector<const Domain*> domains) {
    domains.erase(
        unique(begin(domains), end(domains),
               [](const Domain* lhs, const Domain* rhs) {
                 return IsSubOrSuperDomain(*lhs, *rhs);
               }),
        end(domains)
    );
    return domains;
  }
};


vector<Domain> ReadDomains(istream& in_stream = cin) {
  vector<Domain> domains;

  size_t count;
  in_stream >> count;
  domains.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    string domain_text;
    in_stream >> domain_text;
    domains.emplace_back(domain_text);
  }
  return domains;
}

vector<bool> CheckDomains(const vector<Domain>& banned_domains, const vector<Domain>& domains_to_check) {
  const DomainChecker checker(begin(banned_domains), end(banned_domains));

  vector<bool> check_results;
  check_results.reserve(domains_to_check.size());
  for (const Domain& domain_to_check : domains_to_check) {
    check_results.push_back(!checker.IsSubdomain(domain_to_check));
  }

  return check_results;
}

void PrintCheckResults(const vector<bool>& check_results, ostream& out_stream = cout) {
  for (const bool check_result : check_results) {
    out_stream << (check_result ? "Good" : "Bad") << "\n";
  }
}

void TestSplit(){
	string InputString = "yandex.google.main.page.ru.com";
	vector<string_view> result = Split(InputString, ".");
	vector<string_view> expected = {"yandex", "google", "main", "page", "ru", "com"};
	AssertEqual(result.size(), expected.size() , "TestSplit - Check Sizes");
	AssertEqual(result, expected , "TestSplit - Check Values");
}

void TestGetReversedParts(){
	Domain test_domain("domain.system.verilog.com");
	vector<string_view> expected = {"com", "verilog", "system", "domain"};
	auto range = test_domain.GetReversedParts();
	vector<string_view> result(range.begin(), range.end());
	AssertEqual(result.size(), expected.size(), "ReversedPartsMethod - Check Sizes");
	AssertEqual(result, expected, "ReversedPartsMethod - Check values");
}

void TestSelfSubdomain(){
	Domain test_domain("google.com");
	AssertEqual(IsSubdomain(test_domain, test_domain), true, "Domain is not SubDomain");
}


void SubDomainAndDomainErrorReplacement(){
	Domain sub_test_domain("yandex.google.com");
	Domain test_domain("google.com");
	AssertEqual(IsSubdomain(sub_test_domain, test_domain), true, "Right order");
	AssertEqual(IsSubdomain(test_domain, sub_test_domain), false, "False order");
}

void AbsorbProhibitedDomains(){
	vector<Domain> prohibited_domains = {Domain{"yandex.google.com"},
			Domain{"google.com"}, Domain{"ya.yandex.google.com"},
			Domain{"la.yandex.google.com"}};
	vector<Domain> domains_to_check = {Domain{"obama.google.com"}, Domain{"yu.obama.google.com"}, Domain{"ya.yandex"}};
	DomainChecker checker(prohibited_domains.begin(), prohibited_domains.end());
	vector<bool> results;
	for(const auto& domain : domains_to_check)
		results.push_back(checker.IsSubdomain(domain));
	vector<bool> expected_results = {true, true, false};
	AssertEqual(results, expected_results, "Check Absorb");
	prohibited_domains[1] = Domain{"liberaxo.ru"};
	results.clear();
	expected_results = {false, false, false};
	for(const auto& domain : domains_to_check){
		results.push_back(checker.IsSubdomain(domain));
	}
	AssertEqual(results, expected_results, "Durty method to check");
	vector<Domain> dom = {Domain{"ya.ru"}, Domain{"m.ya.ru"}};
	DomainChecker second(dom.begin(), dom.end());
	AssertEqual(second.IsSubdomain(Domain{"pets.ya.ru"}), true, "Last test");

}

void TrueFalseChecked(){
	vector<Domain> prohibited_domains = {Domain{"vk.google.com"}, Domain{"yandex.ru"}, Domain{"miem.hse.edu"}};
	vector<Domain> domains_to_check = {Domain{"obama.ch"}, Domain{"microsoft.yandex.ru"}};
	DomainChecker checker(prohibited_domains.begin(), prohibited_domains.end());
	AssertEqual(checker.IsSubdomain(domains_to_check[0]), false, "First domain checked");
	AssertEqual(checker.IsSubdomain(domains_to_check[1]), true, "Second domain checked");
}

void TestOutput(){
	ostringstream stream;
	vector<Domain> prohibited_domains = {Domain{"vk.google.com"}, Domain{"yandex.ru"}, Domain{"miem.hse.edu"}};
	vector<Domain> domains_to_check = {Domain{"obama.ch"}, Domain{"microsoft.yandex.ru"}, Domain{"jui.kolba"}, Domain{"mvp.miem.hse.edu"}};
	vector<bool> result = CheckDomains(prohibited_domains, domains_to_check);
	PrintCheckResults(result,stream);
	string expected_result = "Good\nBad\nGood\nBad\n";
	AssertEqual(stream.str(), expected_result, "Bad Good Test");
}

void TestInput(){
	stringstream input_stream;
	input_stream << "5" << endl;
	input_stream << "ya.ya" << endl;
	input_stream << "obama.kb" << endl;
	input_stream << "fsb.ru" << endl;
	input_stream << "lola.ya" << endl;
	input_stream << "tele2.com" << endl;
	vector<Domain> red_domains = ReadDomains(input_stream);
	vector<Domain> expected_domains = {Domain{"ya.ya"}, Domain{"obama.kb"},
			Domain{"fsb.ru"},Domain{"lola.ya"},Domain{"tele2.com"}};
	AssertEqual(red_domains.size(), expected_domains.size(), "Check sizes - Test Input");
	AssertEqual(red_domains, expected_domains, "Check values - Test Input");
}

//void TestSimple() {
//  // Your tests here
//	TestSplit();
//	TestGetReversedParts();
//}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplit);
  RUN_TEST(tr, TestGetReversedParts);
  RUN_TEST(tr, TestSelfSubdomain);
  RUN_TEST(tr, SubDomainAndDomainErrorReplacement);
  RUN_TEST(tr, AbsorbProhibitedDomains);
  RUN_TEST(tr, TrueFalseChecked);
  RUN_TEST(tr, TestOutput);
  RUN_TEST(tr, TestInput);
  const vector<Domain> banned_domains = ReadDomains();
  const vector<Domain> domains_to_check = ReadDomains();
  PrintCheckResults(CheckDomains(banned_domains, domains_to_check));
  return 0;
}
