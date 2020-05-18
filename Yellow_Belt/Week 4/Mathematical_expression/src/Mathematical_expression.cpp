#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

struct arithmetic_operation
{
	int Priority;
	string operation;

	friend istream& operator>>(istream& inp, arithmetic_operation& i);
	arithmetic_operation operator=(const arithmetic_operation& right){
		operation = right.operation;
		Priority = right.Priority;
		return *this;
	}
	friend bool operator>(const arithmetic_operation& left, const arithmetic_operation& right);
};

istream& operator>>(istream& inp, arithmetic_operation& i)
{
	inp >> i.operation;
	if(i.operation == "-" || i.operation == "+")
	{
		i.Priority = 1;
	}
	else if(i.operation == "*" || i.operation == "/"){
		i.Priority = 2;
	}
	return inp;
}

bool operator>(const arithmetic_operation& left, const arithmetic_operation& right){
	return left.Priority > right.Priority;
}

void first_expression_type()
{
	int initial;
	cin >> initial;
	deque<string> expression;
	int num_of_operation;
	cin >> num_of_operation;
	bool is_empty = (num_of_operation == 0);
	is_empty ? expression.push_back(to_string(initial)) :
			expression.push_back(("(" + to_string(initial) + ")"));
	while(num_of_operation != 0)
	{
		string operation;
		cin >> operation;
		int number;
		cin >> number;
		expression.push_back((" " + operation + " "));
		expression.push_back(to_string(number));
		if(num_of_operation != 1){
			expression.push_back(")");
			expression.push_front("(");
		}
		num_of_operation--;
	}
	for(auto const& elem: expression){
		cout << elem;
	}
	cout << endl;
}

void second_expression_type()
{
	int initial_num;
	deque<string> expression;
	int num_of_operation;
	cin >> initial_num >> num_of_operation;
	arithmetic_operation tmp_operation;
	expression.push_back(to_string(initial_num));
	for(int i = 1; i <= num_of_operation; ++i)
	{
		arithmetic_operation operation;
		cin >> operation;
		if(i == 1)
		{
			tmp_operation = operation;
		}
		int num;
		cin >> num;
		if(operation > tmp_operation)
		{
			expression.push_back(")");
			expression.push_front("(");
		}
		expression.push_back((" " + operation.operation + " "));
		tmp_operation = operation;
		expression.push_back(to_string(num));

	}
	for(auto const& elem: expression){
		cout << elem;
	}
	cout << endl;
}



int main() {
//	first_expression_type();
	second_expression_type();
	return 0;
}
