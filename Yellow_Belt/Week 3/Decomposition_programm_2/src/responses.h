#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct BusesForStopResponse{
	vector<string> buses;
};
ostream& operator << (ostream& os, const BusesForStopResponse& r);
struct StopsForBusResponse
{
	map<string, vector<string>> buses_to_stops;
	string bus;
	vector<string> stops;
};
ostream& operator << (ostream& os, const StopsForBusResponse& r);
struct AllBusesResponse {
	map<string, vector<string>> stops_to_buses;
};
ostream& operator << (ostream& os, const AllBusesResponse& r);
