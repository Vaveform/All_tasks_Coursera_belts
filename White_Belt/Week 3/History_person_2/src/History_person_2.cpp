#include <iostream>
#include <map>
#include <string>

using namespace std;

class Person {
public:
	string GetFullNameWithHistory(int year)
	{
		string result = GetFullName(year);
		if(result == "Incognito")
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
	void GetFull()
	{
		for(auto& item: first_names)
		{
			cout << item.first << ":" << item.second << endl;
		}
		cout << "----------------------------" << endl;
		for(auto& item: last_names)
		{
			cout << item.first << ":" << item.second << endl;
		}
	}
  void ChangeFirstName(int year, const string& first_name)
  {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name)
  {
    last_names[year] = last_name;
  }
  string GetFullName(int year)
  {
	string result;
	string name;
	string last_name;
    if(first_names.size()==0 && last_names.size()==0)
    {
    	result = "Incognito";
    }
    else if(first_names.size()!=0 && last_names.size()==0)
    {
    	if(year >= (*first_names.begin()).first)
    	{
    		auto prev_name = prev(first_names.upper_bound(year),1);
    		name = (*prev_name).second;
    		result = name + " " + "with unknown last name";
    	}
    	else
    	{
    		result = "Incognito";
    	}
    }
    else if(first_names.size()==0 && last_names.size()!=0)
    {
    	if(year >= (*last_names.begin()).first)
    	{
    		auto prev_last_name = prev(last_names.upper_bound(year),1);
    		last_name = (*prev_last_name).second;
    		result = last_name + " " + "with unknown first name";
    	}
    	else
    	{
    		result =  "Incognito";
    	}
    }
    else
    {
    	if(year >= (*first_names.begin()).first && year >= (*last_names.begin()).first)
    	{
    		auto prev_name = prev(first_names.upper_bound(year),1);
    		auto prev_last_name = prev(last_names.upper_bound(year),1);
    		name = (*prev_name).second;
    		last_name = (*prev_last_name).second;
    		result = name + " " + last_name;
    	}
    	else if(year >= (*first_names.begin()).first && year < (*last_names.begin()).first)
    	{
    		auto prev_name = prev(first_names.upper_bound(year),1);
			name = (*prev_name).second;
			result = name + " " + "with unknown last name";
    	}
    	else if(year < (*first_names.begin()).first && year >= (*last_names.begin()).first)
    	{
    		auto prev_last_name = prev(last_names.upper_bound(year),1);
			last_name = (*prev_last_name).second;
			result = last_name + " " + "with unknown first name";
    	}
    	else
    	{
    		result = "Incognito";
    	}
    }
    return result;
  }

private:
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
  string FindByName(const map<int,string> &input,int year)
  {
	string result;
	for(auto const &item: input)
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
};

int main()
{
	return 0;
}
