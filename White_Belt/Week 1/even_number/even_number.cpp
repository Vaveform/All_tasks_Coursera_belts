#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	int A, B;
	cin >> A >> B;
	for(int i = A; i <= B; i++)
	{
		if(i % 2 == 0)
		{
			cout << i << " ";
		}
	}
	cout << endl;
}
