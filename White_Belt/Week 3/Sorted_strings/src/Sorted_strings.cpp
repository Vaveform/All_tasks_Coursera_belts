
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings
{
public:
	void AddString(const string& s)
	{
		stroka.push_back(s);
	}
	vector<string> GetSortedStrings()
	{
		sort(begin(stroka), end(stroka));
		return stroka;
	}
private:
	vector<string> stroka;
};

int main()
{
	return 0;
}

