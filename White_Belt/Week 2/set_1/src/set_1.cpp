
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
	set<string> result;
	string elem;
	int n;
	cin >> n;
	while(n > 0)
	{
		cin >> elem;
		result.insert(elem);
		n--;
	}
	cout << result.size();
	return 0;
}
