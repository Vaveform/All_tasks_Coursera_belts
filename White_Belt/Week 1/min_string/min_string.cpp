#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main() {
	string first, second, third;
	cin >> first >> second >> third;
	vector<string> dict = {first, second, third};
	sort(dict.begin(), dict.end());
	cout << dict[0] << endl;
	return 0;
}
