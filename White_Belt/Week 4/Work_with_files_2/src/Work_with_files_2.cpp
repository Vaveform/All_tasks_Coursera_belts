//============================================================================
// Name        : Work_with_files_2.cpp
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
	ofstream output("output.txt");  //ios:app - флажок, дописывает данные в файл
	string line;
	while(getline(input,line))
	{
		output << line << endl;
	}
	return 0;
}
