#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string FindByYear(const map<int,string>& dict, int year)
{
	string result;
	for(auto const &item: dict)
	{
		if(item.first <= year)
		{
			result = item.second;
		}
		else{
			break;
		}
	}
	return result;
}

class Person {
public:
	Person(const string& New_name, const string& New_last_name, int new_birth_day){
		birth_day = new_birth_day;
		first_names[new_birth_day] = New_name;
		last_names[new_birth_day] = New_last_name;
	}
   string GetFullNameWithHistory(int year) const
   {
		string result = GetFullName(year);
		if(result == "No person"){
			return result;
		}
		else if(result == "Incognito")
		{
			return result;
		}
		else if(result.find("with unknown last name") != -1)
		{
			string Name_History = Make_History(year, first_names);
			result = result.insert(result.find(" "), Name_History);
		}
		else if(result.find("with unknown first name") != -1)
		{
			string Last_Name_History = Make_History(year, last_names);
			result = result.insert(result.find(" "), Last_Name_History);
		}
		else
		{
			string Name_History = Make_History(year, first_names);
			string Last_Name_History = Make_History(year, last_names);
			result = result.insert(result.find(" "), Name_History);
			result.append(Last_Name_History);
		}
		return result;
  }
  void ChangeFirstName(int year, const string& first_name)
  {
	  if(year > birth_day){
		  first_names[year] = first_name;
	  }
  }
  void ChangeLastName(int year, const string& last_name)
  {
	  if(year > birth_day){
		  last_names[year] = last_name;
	  }
  }
  string GetFullName(int year) const
  {
	const string name = FindByYear(first_names, year);
	const string last_name = FindByYear(last_names, year);
	if(year < birth_day){
		return "No person";
	}
	else if(name.empty() == true && last_name.empty() == true)
	{
		return "Incognito";
	}
	else if(name.empty() == false && last_name.empty() == true)
	{
		return name + " " + "with unknown last name";
	}
	else if(name.empty() == true && last_name.empty() == false)
	{
		return last_name + " " + "with unknown first name";
	}
	else
	{
		return name + " " + last_name;
	}
  }

private:
  int birth_day;
  map<int,string> first_names;
  map<int,string> last_names;
  string Make_History(int year, const map<int, string>& dict) const
  {
	  auto i = dict.upper_bound(year);
   	  i--;
   	  string tmp = (*i).second;
   	  string History = " (";
   	  for(auto it = dict.rbegin(); it!= dict.rend(); it++)
   	  {
   		  if((*it).first <= (*i).first)
   		  {
   			  if(tmp != (*it).second)
   			  {
   				History = History + (*it).second + ", ";
   			  }
   			  tmp = (*it).second;
   		  }
   	  }
   	  if(History.size() == 2)
   	  {
   		  History = "";
   	  }
   	  else{
   		  History.pop_back();
   		  History.pop_back();
   		  History += ")";
   	  }
   	  return History;
  }
};

int main()
{
//	Person person;
//	person.ChangeFirstName(1965, "Polina");
//	    person.ChangeLastName(1967, "Sergeeva");
//	    for (int year : {1900, 1965, 1990}) {
//	        cout << person.GetFullNameWithHistory(year) << endl;
//	    }
//
//	    person.ChangeFirstName(1970, "Appolinaria");
//	    for (int year : {1969, 1970}) {
//	        cout << person.GetFullNameWithHistory(year) << endl;
//	    }
//
//	    person.ChangeLastName(1968, "Volkova");
//	    for (int year : {1969, 1970}) {
//	        cout << person.GetFullNameWithHistory(year) << endl;
//	    }
//
//	    person.ChangeFirstName(1990, "Polina");
//	    person.ChangeLastName(1990, "Volkova-Sergeeva");
//	    cout << person.GetFullNameWithHistory(1990) << endl;
//
//	    person.ChangeFirstName(1966, "Polina");
//	    cout << person.GetFullNameWithHistory(1966) << endl;
//
//	    person.ChangeLastName(1960, "Sergeeva");
//	    for (int year : {1960, 1967}) {
//	        cout << person.GetFullNameWithHistory(year) << endl;
//	    }
//
//	    person.ChangeLastName(1961, "Ivanova");
//	    cout << person.GetFullNameWithHistory(1967) << endl;
//
//	    person.ChangeLastName(1989, "Volkova-Sergeeva");
//	    cout << person.GetFullNameWithHistory(1995) << endl;
//	person.ChangeLastName(1910, "Ivanov");
//	person.ChangeLastName(1910, "Sokolov");
//	cout << person.GetFullNameWithHistory(1940) << endl;
//	cout << person.GetFullName(1940) << endl;
	return 0;
}
