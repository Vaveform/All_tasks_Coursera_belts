#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements)
{
	sort(elements.begin(), elements.end());
	auto last = unique(elements.begin(), elements.end());
	elements.erase(last, elements.end());
}

int main() {
	vector<int> p = {1,2,2,4,3,5,2,1,6,7,8};
	vector<string> l = {"jopa", "hui", "jopa", "lola", "pola", "pola", "yandex"};
	vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
	RemoveDuplicates(p);
	RemoveDuplicates(l);
	RemoveDuplicates(v2);
	for(const auto& elem: v2){
		cout << elem << " ";
	}
	cout << endl;
	return 0;
}
