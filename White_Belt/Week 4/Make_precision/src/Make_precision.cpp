//============================================================================
// Name        : Make_precision.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
	ifstream input("input.txt");
	double line;
	cout << fixed << setprecision(3);
	while(input >> line)
	{
		cout << line << endl;
	}
	return 0;
}
