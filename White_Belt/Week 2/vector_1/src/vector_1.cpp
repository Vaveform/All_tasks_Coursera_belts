#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector(const vector<int>& p)
{
	cout << p.size() << endl;
	for(auto num: p)
	{
		cout << num << " ";
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	vector<int> tempretures(n);
	vector<int> results;
	int average = 0;
	for(int& t : tempretures)
	{
		cin >> t;
		average+= t;
	}
	average/= n;
	for(int i=0; i < tempretures.size(); ++i)
	{
		if(tempretures[i] > average)
		{
			results.push_back(i);
		}
	}
	PrintVector(results);
	return 0;
}
