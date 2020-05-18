#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <utility>
#include <tuple>
#include <set>
using namespace std;

struct Date {
  int year, month, day;
  friend bool operator == (const Date& lhs, const Date& rhs);
  friend bool operator<(const Date& lhs, const Date& rhs);
  friend bool operator>(const Date& lhs, const Date& rhs);
  friend ostream& operator<< (ostream& input,const Date& date);
};

ostream& operator<< (ostream& input,const Date& date);

struct Time {
  int hours, minutes;
  friend bool operator < (const Time& lhs, const Time& rhs);
  friend bool operator > (const Time& lhs, const Time& rhs);
  friend bool operator == (const Time& lhs , const Time& rhs);
  friend ostream& operator<< (ostream& input, const Time& time);
};

ostream& operator<< (ostream& input, const Time& time);

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
  friend ostream& operator<<(ostream& input, const AirlineTicket& ticket);
};

ostream& operator<<(ostream& input, const AirlineTicket& ticket);
