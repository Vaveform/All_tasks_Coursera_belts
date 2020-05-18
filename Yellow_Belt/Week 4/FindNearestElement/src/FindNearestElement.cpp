#include "Unit_test_framework.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include <exception>
#include <string>
#include <map>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers,int border)
{
	if(numbers.empty()){
		return numbers.end();
	}
	auto it_right = numbers.upper_bound(border);
	auto it_left = prev(it_right);
	if(it_left != numbers.end() && it_right !=numbers.end()){
		return border - *it_left <= *it_right - border ? it_left : it_right;
	}
	else if(it_left == numbers.end() && it_right != numbers.end()){
		return it_right;
	}
	else if(it_left != numbers.end() && it_right == numbers.end()){
		return it_left;
	}
	else{
		return numbers.end();
	}
}

void Test_1()
{
	{
		set<int> numbers = {1,2,4,10,15,25};
		AssertEqual(*FindNearestElement(numbers, -100), 1, "test_1");
		AssertEqual(*FindNearestElement(numbers, 1), 2, "test_2");
		AssertEqual(*FindNearestElement(numbers, 2), 1, "test_3");
		AssertEqual(*FindNearestElement(numbers, 4), 2, "test_4");
		AssertEqual(*FindNearestElement(numbers, 10), 15, "test_5");
		AssertEqual(*FindNearestElement(numbers, 100), 25, "test_6");
		AssertEqual(*FindNearestElement(numbers, 3), 2, "test_7");
		AssertEqual(*FindNearestElement(numbers, 5), 4, "test_8");
		AssertEqual(*FindNearestElement(numbers, 6), 4, "test_9");
    }
	{
		set<int> numbers = {1,3,5,7,9,11};
		AssertEqual(*FindNearestElement(numbers, 2), 1, "test_10");
		AssertEqual(*FindNearestElement(numbers, 4), 3, "test_11");
		AssertEqual(*FindNearestElement(numbers, 6), 5, "test_12");
		AssertEqual(*FindNearestElement(numbers, 8), 7, "test_13");
		AssertEqual(*FindNearestElement(numbers, 10), 9, "test_14");
		AssertEqual(*FindNearestElement(numbers, -10), 1, "test_15");
		AssertEqual(*FindNearestElement(numbers, 1), 3, "test_16");
	}
	{
		set<int> numbers = {-11, -9, -7, -5, -3, -1};
		AssertEqual(*FindNearestElement(numbers, 10), -1, "test_17");
		AssertEqual(*FindNearestElement(numbers, -40), -11, "test_18");
		AssertEqual(*FindNearestElement(numbers, -10), -11, "test_19");
		AssertEqual(*FindNearestElement(numbers, -8), -9, "test_20");
		AssertEqual(*FindNearestElement(numbers, -6), -7, "test_21");
	}
	{
		set<int> numbers = {1};
		AssertEqual(*FindNearestElement(numbers, 1), 1, "test_22");
	}
}

int main()
{
	TestRunner runner;
	runner.RunTest(Test_1, "Run");
	set<int> numbers = {1, 4, 6};
	  cout <<
	      *FindNearestElement(numbers, 0) << " " <<
	      *FindNearestElement(numbers, 3) << " " <<
	      *FindNearestElement(numbers, 5) << " " <<
	      *FindNearestElement(numbers, 6) << " " <<
	      *FindNearestElement(numbers, 100) << endl;

	  set<int> empty_set;

	  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;

}
