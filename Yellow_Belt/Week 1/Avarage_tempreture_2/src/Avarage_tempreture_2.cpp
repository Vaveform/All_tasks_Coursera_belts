#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main()
{
	int k, count = 0;
	int64_t avg = 0;
	cin >> k;
	vector<int> tempretures(k);
	for(int& elem: tempretures){
		cin >> elem;
		avg += elem;
	}
	avg = avg/static_cast<int>(tempretures.size());
	cout <<
			count_if(tempretures.begin(),tempretures.end(),
					[avg](int i)
					{
		return i > avg;
					}) << endl;
	for(const int& elem: tempretures){
		if(elem > avg){
			cout << count << " ";
		}
		count++;
	}
	cout << endl;
	return 0;
}
