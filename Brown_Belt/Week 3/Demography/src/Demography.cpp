#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <optional>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  bool is_male;
};

vector<Person> ReadPeople(istream& input, vector<int>& ages, vector<int>& incomes) {
  size_t count;
  input >> count;
  ages.resize(count);
  incomes.resize(count);
  vector<Person> result(count);
  for (size_t i = 0; i < count; i++) {
    char gender;
    input >> result[i].name;
    input >> ages[i];
    input >> incomes[i];
    input >> gender;
    result[i].is_male = gender == 'M';
//    input >> p.name >> p.age >> p.income >> gender;
//    ages
//    p.is_male = gender == 'M';
  }

  return result;
}

class DemographyDB{
public:
	explicit DemographyDB(vector<int> sorted_ages_, vector<int> sorted_incomes_,
			optional<string> popular_men_, optional<string> popular_women_ ) :
			sorted_ages(move(sorted_ages_)),sorted_incomes(move(sorted_incomes_)), popular_men_names(popular_men_),
			popular_women_names(popular_women_)
	{
	}
	size_t GetNumberOfPeopleByAge(int adult_age) const{
		auto adult_begin = lower_bound(
			begin(sorted_ages), end(sorted_ages), adult_age, [](const int& lhs, int age) {
			  return lhs < age;
			}
		  );
		return distance(adult_begin, sorted_ages.end());
	}
	int SumOfTopXIncomes(int x) const{
		auto Top = Head(sorted_incomes, x);
		return accumulate(Top.begin(), Top.end(), 0);
	}
	const optional<string>& GetPopularMenName() const{
		return popular_men_names;
	}
	const optional<string>& GetPopularWomenName() const {
		return popular_women_names;
	}
private:
	const vector<int> sorted_ages;
	const vector<int> sorted_incomes;
	const optional<string> popular_men_names;
	const optional<string> popular_women_names;
};

template<typename InputIt>
optional<string> Find_In_Sorted_Range_Name(InputIt begin, InputIt end){
	optional<string> result = {};
	if(begin != end){
		sort(begin, end, [](const Person& lhs, const Person& rhs){
			return lhs.name < rhs.name;
		});
		const string* most_popular_name = &begin->name;
		int count = 1;
		for (auto i = begin; i != end; ) {
		  auto same_name_end = find_if_not(i, end, [i](const Person& p) {
			return p.name == i->name;
		  });
		  auto cur_name_count = std::distance(i, same_name_end);
		  if (cur_name_count > count) {
			count = cur_name_count;
			most_popular_name = &i->name;
		  }
		  i = same_name_end;
		}
		result = *most_popular_name;
	}
	return result;
}

pair<optional<string>, optional<string>> Find_by_names(vector<Person>& people){
	pair<optional<string>, optional<string>> result = {{}, {}};
	auto it_partioned = partition(begin(people), end(people), [](Person& p){
		return p.is_male == true; // is_male gender = true
	});
	IteratorRange only_m{people.begin(), it_partioned};
	IteratorRange only_w{it_partioned, people.end()};
	result.first = Find_In_Sorted_Range_Name(only_m.begin(), only_m.end());
	result.second = Find_In_Sorted_Range_Name(only_w.begin(), only_w.end());
	return result;
}

int main() {
  vector<int> ages;
  vector<int> incomes;
  vector<Person> people = ReadPeople(cin, ages, incomes);
  auto pair = Find_by_names(people);
  sort(begin(ages), end(ages), [](const int& lhs, const int& rhs){
	  return lhs < rhs;
  });
  sort(begin(incomes), end(incomes), [](const int& lhs, const int& rhs){
	  return lhs > rhs;
  });
  DemographyDB data_base(move(ages), move(incomes), pair.first, pair.second);


  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;

      size_t number_of_people = data_base.GetNumberOfPeopleByAge(adult_age);

      cout << "There are " << number_of_people
           << " adult people for maturity age " << adult_age << '\n';
    }
    else if (command == "WEALTHY") {
      int count;
      cin >> count;
      int sum_of_top_incomes = data_base.SumOfTopXIncomes(count);

      cout << "Top-" << count << " people have total income " << sum_of_top_incomes << '\n';
    }
    else if (command == "POPULAR_NAME") {
      char gender;
      cin >> gender;
      optional<string> most_popular_name;
      if(gender == 'M'){
    	  most_popular_name = data_base.GetPopularMenName();
      }
      else{
    	  most_popular_name = data_base.GetPopularWomenName();
      }
      most_popular_name.has_value() ? cout << "Most popular name among people of gender " << gender << " is "
              << most_popular_name.value() << endl : cout << "No people of gender " << gender << endl;
    }
  }
}
