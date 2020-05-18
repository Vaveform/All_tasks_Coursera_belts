#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void PrintVector(RandomIt range_begin, RandomIt range_end)
{
    for(auto it = range_begin; it != range_end; it++){
        cout << *it << " ";
    }
    cout << endl;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if(range_end - range_begin <= 1)
	{
		return ;
	}
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto begin = elements.begin();
    auto end = elements.end();
    auto middle1 = begin + (end - begin)/3;
    auto middle2 = middle1 + (end - begin)/3;
    MergeSort(begin, middle1);
    MergeSort(middle1, middle2);
    vector<typename RandomIt::value_type> tmp;
    merge(begin, middle1, middle1, middle2, back_inserter(tmp));
    MergeSort(middle2, end);
    merge(tmp.begin(), tmp.end(), middle2, end, range_begin);
}


int main() {
	vector<int> l = {5,2,1,19,5,18,7,3,10};
//	vector<int> p = {16};
//	vector<int> empty;
//	merge(l.begin(), l.end(), p.begin(), p.end(), back_inserter(empty));
	MergeSort(l.begin(), l.end());
//    PrintVector(l.begin(),l.end());
	PrintVector(l.begin(), l.end());
	return 0;
}
