
#include <iostream>
#include <set>
#include <map>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m)
{
	set<string> result;
	for(const auto& item: m)
	{
		result.insert(item.second);
	}
	return result;
}

void PrintSet(const set<string>& s)
{
	for(const auto& elem: s)
	{
		cout << elem << endl;
	}
}

int main()
{
	set<string> values = BuildMapValuesSet({
	    {1, "odd"},
	    {2, "even"},
	    {3, "odd"},
	    {4, "even"},
	    {5, "odd"}
	});
	PrintSet(values);
	return 0;
}
