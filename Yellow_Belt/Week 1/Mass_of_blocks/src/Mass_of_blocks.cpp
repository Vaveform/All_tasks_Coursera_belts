#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main()
{
	int N, R;
	uint64_t sum = 0;
	cin >> N >> R;
	while(N > 0)
	{
		int W, H, D;
		cin >> W >> H >> D;
		sum += W*H*D*R;
		N--;
	}
	cout << sum << endl;
	return 0;
}
