#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
	auto negative = find_if(numbers.begin(), numbers.end(), [](const auto& val){
		return val < 0;
	});
	if(negative != numbers.end()){
		while(negative != numbers.begin()){
			negative--;
			cout << *negative << " ";
		}
		cout << endl;
	}
	else{
		auto l = numbers.end();
		while(l != numbers.begin()){
			l--;
			cout << *l << " ";
		}
		cout << endl;
	}
}

int main()
{
	PrintVectorPart(vector<int>({2,1,3,2,4,-10,4,3,2}));
	PrintVectorPart(vector<int>({2,1,3,2,4,-10,4,3,2,-123,4,5,2}));
	PrintVectorPart(vector<int>({2,1,3,2,4,4,3,2}));
	PrintVectorPart(vector<int>({-2,1,3,2,4,-10,4,3,2}));
	PrintVectorPart(vector<int>({-2}));
	PrintVectorPart(vector<int>({2}));
	PrintVectorPart(vector<int>({2,1,-3,2,4,-10,4,3,-2}));
	PrintVectorPart(vector<int>({-2,1,3,2,4,-10,4,3,2}));
	PrintVectorPart(vector<int>({2,-1,3,-2,4,-10,4,3,-2}));
	return 0;
}
