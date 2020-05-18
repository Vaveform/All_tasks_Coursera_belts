
#include <iostream>
#include <map>
#include <string>
using namespace std;

void change_capital(map<string, string>& countries, string country, string new_capital)
{
	if(countries.find(country) == countries.end())
	{
		countries[country] = new_capital;
		cout << "Introduce new country " << country
				<< " with capital " << countries[country] << endl;
	}
	else if(countries[country] == new_capital)
	{
		cout << "Country " << country << " hasn't changed its capital" << endl;
	}
	else
	{
		string last_capital = countries[country];
		countries[country] = new_capital;
		cout << "Country " << country << " has changed its capital from "
				<< last_capital << " to " << countries[country] << endl;
	}
}

void rename(map<string, string>& countries, string old_country, string new_country)
{
    if(old_country == new_country || countries.find(old_country) == countries.end() || countries.find(new_country) != countries.end())
    {
    	cout << "Incorrect rename, skip" << endl;
    }
    else
    {
    	countries[new_country] = countries[old_country];
    	countries.erase(old_country);
    	cout << "Country " << old_country << " with capital "
    			<< countries[new_country] << " has been renamed to " << new_country << endl;
    }
}
void about(map<string, string>& countries, string country)
{
	if(countries.find(country) == countries.end())
	{
		cout << "Country " << country << " doesn't exist" << endl;
	}
	else
	{
		cout << "Country " << country << " has capital " << countries[country] << endl;
	}
}
void dump(const map<string,string>& countries)
{
	if(countries.size() == 0)
	{
		cout << "There are no countries in the world" << endl;
	}
	else
	{
		for(const auto& item: countries)
		{
			cout << item.first << "/" << item.second << " ";
		}
	}
	cout << endl;
}
int main()
{
	map<string, string> countries;
	int num_of_operations;
	cin >> num_of_operations;
	string operation;
	while(num_of_operations)
	{
		cin >> operation;
		if(operation == "CHANGE_CAPITAL")
		{
			string country, new_capital;
			cin >> country >> new_capital;
			change_capital(countries, country, new_capital);
		}
		else if(operation == "RENAME")
		{
			string old_country, new_country;
			cin >> old_country >> new_country;
			rename(countries, old_country, new_country);
		}
		else if(operation == "ABOUT")
		{
			string country;
			cin >> country;
			about(countries, country);
		}
		else
		{
			dump(countries);
		}
		num_of_operations--;
	}
	return 0;
}
