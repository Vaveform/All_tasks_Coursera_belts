
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

int main() {
	int size;
	cin >> size;
	int *ptr = new int[size];
	for(int i = 0; i < size; ++i)
	{
		cin >> ptr[i];
	}
	sort(ptr, ptr+size, [](int &x, int &y){
	if(abs(x) < abs(y)){
		return true;
	}
	else
	{
		return false;
	}
	 });
	for(int i = 0; i < size; ++i)
	{
		cout << ptr[i] << " ";
	}
	return 0;
}
