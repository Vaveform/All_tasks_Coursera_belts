#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

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

void new_bus(map<string, vector<string>>& routes, map<string, vector<string>>& stopses, int& size ,string bus)
{
	vector<string> stops;
	string stop;
	while(size > 0)
	{
		cin >> stop;
		stopses[stop].push_back(bus);
		stops.push_back(stop);
		size--;
	}
	routes[bus] = stops;
	stops.clear();
}

void buses_for_stop(map<string, vector<string>>& stopses,string stop)
{
	if(stopses.find(stop) != stopses.end())
	{
		PrintVector(stopses[stop]);
	}
	else
	{
		cout << "No stop" << endl;
	}
}

void stops_for_bus(map<string, vector<string>>& routes, map<string, vector<string>>& stopses, string bus)
{
	if(routes.find(bus) == routes.end())
	{
		cout << "No bus" << endl;
	}
	else
	{
		for(const auto& elem: routes[bus])
		{
			if(stopses[elem].size() == 1 && stopses[elem][0] == bus)
			{
				cout << "Stop " << elem << ": " << "no interchange" << endl;
			}
			else
			{
				cout << "Stop " << elem << ": ";
				for(const auto& elemt: stopses[elem])
				{
					if(elemt != bus)
					{
						cout << elemt << " ";
					}
				}
				cout << endl;
			}
		}
	}
}

void all_buses(const map<string, vector<string>>& routes)
{
	if(routes.size() > 0)
	{
	    for(auto& item: routes)
	    {
		    cout << "Bus " << item.first << ": ";
		    PrintVector(item.second);
	    }
	}
	else
	{
		cout << "No buses" << endl;
	}
}

int main()
{
	map<string, vector<string>> routes, stopses;
	int num_of_operation;
	cin >> num_of_operation;
	while(num_of_operation > 0)
	{
		string operation;
		cin >> operation;
		if(operation == "NEW_BUS")
		{
			string name_route;
			int num_of_routes;
			cin >> name_route;
			cin >> num_of_routes;
			new_bus(routes,stopses, num_of_routes, name_route);
		}
		else if(operation == "BUSES_FOR_STOP")
		{
			string stop;
			cin >> stop;
			buses_for_stop(stopses, stop);
		}
		else if(operation == "STOPS_FOR_BUS")
		{
			string bus;
			cin >> bus;
			stops_for_bus(routes,stopses, bus);
		}
		else
		{
			all_buses(routes);
		}
		num_of_operation--;
	}
	return 0;
}
