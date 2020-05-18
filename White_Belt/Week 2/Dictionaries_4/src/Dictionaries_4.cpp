
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int num_of_operation;
	int num_of_bus = 0;
	map<vector<string>, int> buses;
	vector<string> stops;
	cin >> num_of_operation;
	while(num_of_operation > 0)
	{
		int num_of_stops;
		cin >> num_of_stops;
		while(num_of_stops > 0)
		{
			string stop;
			cin >> stop;
			stops.push_back(stop);
			num_of_stops--;
		}
		if(buses.find(stops) == buses.end())
		{
			num_of_bus++;
			buses[stops] = num_of_bus;
			cout << "New bus " << buses[stops] << endl;
		}
		else
		{
			cout << "Already exists for " << buses[stops] << endl;
		}
		stops.clear();
		num_of_operation--;
	}
	return 0;
}
