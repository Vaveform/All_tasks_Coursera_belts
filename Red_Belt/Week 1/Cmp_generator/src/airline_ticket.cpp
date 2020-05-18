#include "airline_ticket.h"


bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date& lhs, const Date& rhs)
{
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator > (const Date& lhs, const Date& rhs){
	return tie(lhs.year, lhs.month, lhs.day) > tie(rhs.year, rhs.month, rhs.day);
}

ostream& operator<<(ostream& input,const Date& date){
	input << setfill('0') << setw(4) << date.year << "-"
								  << setw(2) << date.month << "-"
								  << setw(2) << date.day;
	return input;
}

bool operator < (const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator > (const Time& lhs, const Time& rhs){
	return tie(lhs.hours, lhs.minutes) > tie(rhs.hours, rhs.minutes);
}

bool operator == (const Time& lhs , const Time& rhs){
	return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& input,const Time& time){
	input << time.hours << ":" << time.minutes;
	return input;
}

ostream& operator<<(ostream& input, const AirlineTicket& ticket){
	input << "Ticket from: " << ticket.from << " to: " << ticket.to << "on airline: " << ticket.airline << "\n"
			<< "Departure date and time: " << ticket.departure_date << " " << ticket.departure_time << "\n"
			<< "Arrival date and time: " << ticket.arrival_date << " " << ticket.arrival_time << "\n"
			<< "Ticket price: " << ticket.price;
	return input;
}





