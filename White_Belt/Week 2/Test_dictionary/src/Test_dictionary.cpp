
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string, vector<string>> ReversedMap(const map<string, vector<string>>& p)
{
	map<string, vector<string>> result;
	for(const auto& item: p)
	{
		for(const auto& elem: item.second)
		{
			result[elem].push_back(item.first);
		}
	}
	return result;
}

void PrintVector(const vector<string>& w)
{
	for(const auto& elem: w)
	{
		if(elem != w[w.size() - 1])
		{
		    cout << elem << " ";
		}
		else
		{
			cout << elem;
		}
	}
	cout << endl;
}

int main()
{
	map<string, vector<string>> test = {{"Marino", {"32K", "720", "950"}}, {"Altufievo",{"32K", "950"}}};
	for(const auto& item: test)
	{
		cout << "Stop " << item.first << ": ";
		PrintVector(item.second);
	}
	map<string, vector<string>> result;
	result = ReversedMap(test);
	for(const auto& item: result)
	{
		cout << "Bus " << item.first << ": ";
		PrintVector(item.second);
	}
	return 0;
}
