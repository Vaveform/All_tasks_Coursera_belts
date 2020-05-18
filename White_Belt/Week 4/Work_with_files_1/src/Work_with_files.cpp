//============================================================================
// Name        : Work_with_files.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream input("input.txt");
	string line;
	while(getline(input, line))
	{
		cout << line << endl;
	}
	return 0;
}
