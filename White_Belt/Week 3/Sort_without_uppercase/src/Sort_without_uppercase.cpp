
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

string str_lowercase(string str)
{
	transform(begin(str), end(str), begin(str),
			[](unsigned char c){
		return tolower(c);
	}
	);
	return str;
}

int main() {
	vector<string> input;
	int num = 0;
	string elem;
	cin >> num;
	for(int i = 0; i < num; ++i)
	{
		cin >> elem;
		input.push_back(elem);
	}
	sort(begin(input), end(input), [](string x, string y){
	return str_lowercase(x) < str_lowercase(y);} ) ;
	for(const auto& i: input)
	{
		cout << i << " ";
	}
	cout << endl;
	return 0;
}
