#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if(r.buses.size() == 0){
		cout << "No stop" << endl;
	}
	else{
		for(const auto& bus: r.buses){
			cout << bus << " ";
		}
		cout << endl;
	}
	return os;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if(r.bus.size() == 0){
		cout << "No bus" << endl;
	}
	else{
		for(const string& stop: r.stops){
			cout << "Stop " << stop << ": ";
			if(r.buses_to_stops.at(stop).size() == 1){
				cout << "no interchange";
			}
			else{
				for(const string& other_bus: r.buses_to_stops.at(stop)){
					if(r.bus != other_bus){
						cout << other_bus << " ";
					}
				}
			}
			cout << endl;
		}
	}
	return os;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if(r.stops_to_buses.empty()){
		cout << "No buses" << endl;
	}
	else{
		for(const auto& bus: r.stops_to_buses){
			cout << "Bus " << bus.first << ": ";
			for(const string& stop: bus.second){
				cout << stop << " ";
			}
			cout << endl;
		}
	}
	return os;
};

