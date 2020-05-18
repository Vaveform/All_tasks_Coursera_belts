#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

#define SORT_BY(field)                                       \
	[](const AirlineTicket& lhs, const AirlineTicket& rhs){  \
	    return lhs.field < rhs.field;                        \
    }                                                        \


void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

void TestDateCmp(){
	{
	    Date d1 = {2019, 3, 4};
	    Date d2 = {2018, 5, 6};
	    bool result_cmp = (d1 < d2);
	    ASSERT_EQUAL(result_cmp, false);
	}
	{
		Date d1 = {2019, 5, 6};
		Date d2 = {2019, 5, 6};
		bool result_cmp = (d1 < d2);
        ASSERT_EQUAL(result_cmp, false);
	}
	{
		Date d1 = {2019, 4, 6};
		Date d2 = {2019, 5, 6};
		bool result_cmp = (d1 < d2);
		ASSERT_EQUAL(result_cmp, true);
	}
	{
		Date d1 = {2019, 5, 1};
		Date d2 = {2019, 5, 6};
		bool result_cmp = (d1 < d2);
		ASSERT_EQUAL(result_cmp, true);
	}
	{
		Date d1 = {2019, 15, 6};
		Date d2 = {2029, 11, 6};
		bool result_cmp = (d1 < d2);
		ASSERT_EQUAL(result_cmp, true);
	}
	{
		Date d1 = {2029, 15, 6};
		Date d2 = {2029, 15, 8};
		bool result_cmp = (d1 < d2);
		ASSERT_EQUAL(result_cmp, true);
	}
}

void TestTimeCmp(){
	{
		Time t1 = {21, 45};
		Time t2 = {22, 45};
		bool result_cmp = (t1 < t2);
		ASSERT_EQUAL(result_cmp, true);
	}
	{
		Time t1 = {21, 44};
		Time t2 = {21, 52};
		bool result_cmp = (t1 < t2);
		ASSERT_EQUAL(result_cmp, true);
	}
	{
		Time t1 = {21, 44};
		Time t2 = {21, 44};
		bool result_cmp = (t1 < t2);
		ASSERT_EQUAL(result_cmp, false);
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
  RUN_TEST(tr, TestDateCmp);
  RUN_TEST(tr, TestTimeCmp);
  return 0;
}
