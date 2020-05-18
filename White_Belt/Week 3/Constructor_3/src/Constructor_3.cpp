
#include <iostream>
using namespace std;

struct Incognizable
{
	int first = 0;
	int second = 0;
};

int main()
{
	Incognizable a;
	Incognizable b = {};
	Incognizable c = {0};
	Incognizable d = {0, 1};
	cout << a.first << " " << a.second << endl;
	cout << b.first << " " << b.second << endl;
	cout << c.first << " " << c.second << endl;
	cout << d.first << " " << d.second << endl;
	return 0;
}
