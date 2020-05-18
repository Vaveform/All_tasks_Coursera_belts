#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//vector<string> SplitIntoWords(const string& s) - simple solution with using streams in C++
//{
//	vector<string> result;
//	stringstream ss(s);
//	string elem;
//	while(getline(ss, elem, ' ')){
//		result.push_back(elem);
//	}
//	return result;
//}

vector<string> SplitIntoWords(const string& s)
{
	int size = count(s.begin(), s.end(), ' ') + 1;
	vector<string> result(size);
	auto start = s.begin();
	for(int i = 0; i < size; i++){
		auto end_s = find(start, s.end(),' ');
		string elem(start,end_s);
		end_s++;
		start = end_s;
		result[i] = elem;
	}
	return result;
}

int main()
{
//	for(const auto& elem: SplitIntoWords("wwqwd ewfwefw wefwefwe")){
//		cout << elem << endl;
//	}
//	SplitIntoWords("wwqwd ewfwefw wefwefwe");
	return 0;
}
