
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;



void PrintVector(const vector<bool>& p)
{
	for(auto num: p)
	{
		cout << num << " ";
	}
	cout << endl;
}

void come(vector<bool>& deque, int& num)
{
	while(num > 0)
	{
		deque.push_back(true);
		num--;
	}
}

void worry(vector<bool>& deque, int index)
{
	deque.at(index) = false;
}

void deleted(vector<bool>& deque, int& num)
{
	while(num < 0)
	{
		deque.pop_back();
		num++;
	}
}

void quiet(vector<bool>& deque, int index)
{
	deque.at(index) = true;
}

void worry_count(const vector<bool>& deque)
{
	cout << count(deque.begin(), deque.end(), false) << endl;
}

int main()
{
	vector<bool> deque;
	int operations;
	string operation;
	int parametr;
	cin >> operations;
	while(operations > 0)
	{
		cin >> operation;
		if(operation != "WORRY_COUNT")
		{
			cin >> parametr;
			if(operation == "COME" && parametr > 0)
			{
			    come(deque, parametr);
			}
			else if(operation == "COME" && parametr < 0)
			{
			    deleted(deque, parametr);
			}
			else if(operation == "QUIET")
			{
			    quiet(deque, parametr);
			}
			else
			{
				worry(deque, parametr);
			}
		}
		else
		{
			worry_count(deque);
		}
		operations--;
	}
	return 0;
}
