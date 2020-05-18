#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	if(a < b)
	{
		swap(a, b);
	}
	while(a % b != 0)
	{
	    int tmp = b;
		b = a % b;
		a = tmp;
	}
	cout << b << endl;
	return 0;
}
