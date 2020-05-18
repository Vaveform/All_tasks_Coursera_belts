#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	vector<int> v;
	int count = 0;
	int num;
	cin >> num;
	int tmp = num;
	while(num >= 2)
	{
		num /= 2;
		count += 1;
	}
	num = tmp;
	while(count >= 0)
	{
		tmp = num / pow(2, count);
		cout << tmp % 2;
		count--;
	}
}
