#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

// ���� ��� ����������, ���������� ������ ������
string FindNameByYear(const map<int, string>& names, int year)
{
	string result;
	if(year < (*names.begin()).first)
	{
		return result;
	}
	auto iterator = prev(names.upper_bound(year));
	result = (*iterator).second;
	return result;
}

class Person {
public:
	 void All()
	    {
	    	for(auto item: first_names)
	    	{
	    		cout << item.first << ": " << item.second  << endl;
	    	}
	    	cout << "----------------------------" << endl;
	    	for(auto item: last_names)
	    	{
	    		cout << item.first << ": " << item.second  << endl;
	    	}
	    }
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // �������� ��� � ������� �� ��������� �� ��� year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // ���� � ���, � ������� ����������
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // ���� ���������� ������ ���
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // ���� ���������� ������ �������
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // ���� �������� � ���, � �������
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};

int main() {
	Person person;

	  person.ChangeFirstName(1965, "Polina");
	  person.ChangeLastName(1967, "Sergeeva");
	  for (int year : {1900, 1965, 1990}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeFirstName(1970, "Appolinaria");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

	  person.ChangeLastName(1968, "Volkova");
	  for (int year : {1969, 1970}) {
	    cout << person.GetFullName(year) << endl;
	  }

  return 0;
}


