
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>

using namespace std;


int main()
{
	map<set<string>, int> buses;
	int n,stops, i = 1;
	string tmp_str;
	set<string> names_stops;
	cin >> n;
	while(n > 0)
	{
		cin >> stops;
		while(stops > 0)
		{
			cin >> tmp_str;
			names_stops.insert(tmp_str);
			stops--;
		}
		if(buses.find(names_stops) != buses.end())
		{
			cout << "Already exists for " << buses[names_stops] << endl;
		}
		else
		{
			cout << "New bus " << i << endl;
			buses[names_stops] = i;
			i++;
		}
		names_stops.clear();
		n--;
	}
	return 0;
}
