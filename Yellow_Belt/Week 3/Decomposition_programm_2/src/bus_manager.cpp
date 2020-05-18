#include "bus_manager.h"


void BusManager::AddBus(const string& bus, const vector<string>& stops)
{
  stops_to_buses[bus] = stops;
  for (const string& stop : stops)
  {
	  buses_to_stops[stop].push_back(bus);
  }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
  BusesForStopResponse result;
  if(buses_to_stops.count(stop) != 0){
	  result.buses = buses_to_stops.at(stop);
  }
  return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
  StopsForBusResponse result;
  if(stops_to_buses.count(bus) != 0){
	  result.bus = bus;
	  for(const string& stop : stops_to_buses.at(bus)){
		  result.stops.push_back(stop);
		  result.buses_to_stops[stop] = buses_to_stops.at(stop);
	  }
  }
  return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
  AllBusesResponse result;
  result.stops_to_buses = stops_to_buses;
  return result;
}
