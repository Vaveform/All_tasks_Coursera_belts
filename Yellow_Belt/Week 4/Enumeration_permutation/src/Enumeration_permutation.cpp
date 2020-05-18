#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

void PrintVector(const vector<int>& elements){
	for(const auto& element: elements){
		cout << element << " ";
	}
	cout << endl;
}

int main() {
	int N;
	cin >> N;
	vector<int> elements(N);
    iota(elements.begin(), elements.end(), 1);
	reverse(elements.begin(), elements.end());
	do{
		PrintVector(elements);
	}
	while(prev_permutation(elements.begin(), elements.end()));
	return 0;
}
