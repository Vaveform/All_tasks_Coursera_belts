//============================================================================
// Name        : Work_with_table.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	int N, M;
	string elem;
	ifstream input("input.txt");
	getline(input, elem, ' ');
	N = stoi(elem);
	getline(input, elem, '\n');
	M = stoi(elem);
	while(N > 0)
	{
		int tmp = M;
		while(M > 0)
		{
			if(M==1){
				getline(input, elem, '\n');
				cout << setw(10) << elem;
			}
			else{
				getline(input, elem, ',');
				cout << setw(10) << elem << " ";
			}
			M--;
		}
		M = tmp;
		if(N != 1){
			cout << endl;
		}
		N--;
	}
	return 0;
}
