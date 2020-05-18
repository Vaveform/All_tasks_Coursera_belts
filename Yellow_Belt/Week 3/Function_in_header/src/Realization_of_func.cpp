#include <algorithm>
#include "sum_reverse_sort.h"

int Sum(int x, int y){
	return x+y;
}

string Reverse(string s){
	string result;
	reverse(s.begin(), s.end());
	result = s;
	return result;
}

void Sort(vector<int>& nums){
	sort(nums.begin(), nums.end());
}




