#include "query.h"

istream& operator >> (std::istream& is, Query& q)
{
	string QueryTypeString;
	is >> QueryTypeString;
	if(QueryTypeString == "NEW_BUS"){
		q.type = QueryType::NewBus;
		is >> q.bus;
		int num_of_stops;
		is >> num_of_stops;
		q.stops.resize(num_of_stops);
		for(auto& stop:q.stops){
			is >> stop;
		}
	}
	else if(QueryTypeString == "BUSES_FOR_STOP"){
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if(QueryTypeString == "STOPS_FOR_BUS"){
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if(QueryTypeString == "ALL_BUSES"){
		q.type = QueryType::AllBuses;
	}
	return is;
};

