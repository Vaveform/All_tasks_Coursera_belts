
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// ���� ��� ����������, ���������� ������ ������
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // ���������� ��� ����������

  // ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
  for (const auto& item : names) {
    // ���� ��������� ��� �� ������ �������, ��������� ���
    if (item.first <= year) {
      name = item.second;
    } else {
      // ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
      break;
    }
  }

  return name;
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
  	    cout << "=======================" << endl;
  	    	    person.All();

  	    person.ChangeFirstName(1970, "Appolinaria");
  	    cout << "=======================" << endl;
  	    	    person.All();

  	    person.ChangeLastName(1968, "Volkova");
  	    cout << "=======================" << endl;
  	    	    person.All();

  	    person.ChangeFirstName(1990, "Polina");
  	    person.ChangeLastName(1990, "Volkova-Sergeeva");
  	    cout << "=======================" << endl;
  	    	    person.All();

  	    person.ChangeFirstName(1966, "Polina");
  	    cout << "=======================" << endl;
  	    	    person.All();


  	    person.ChangeLastName(1960, "Sergeeva");
  	    cout << "=======================" << endl;
  	    	    person.All();

  	    person.ChangeLastName(1961, "Ivanova");
  	    	    cout << "=======================" << endl;
  	    	    	    person.All();

  	    person.ChangeLastName(1989, "Volkova-Sergeeva");
  	    cout << "=======================" << endl;
  	    person.All();


  return 0;
}


