#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if(range_end - range_begin < 2){
		return;
	}
	vector<typename RandomIt::value_type> curr_vec(make_move_iterator(range_begin), make_move_iterator(range_end));
	auto begin = curr_vec.begin();
	auto middle_1 = curr_vec.begin() + (curr_vec.end() - curr_vec.begin()) / 3;
	auto middle_2 = curr_vec.begin() + (curr_vec.end() - curr_vec.begin()) * 2 / 3;
	auto end = curr_vec.end();
	MergeSort(begin, middle_1);
	MergeSort(middle_1, middle_2);
	MergeSort(middle_2, end);
	vector<typename RandomIt::value_type> tmp_vec;
	merge(make_move_iterator(begin), make_move_iterator(middle_1), make_move_iterator(middle_1), make_move_iterator(middle_2), back_inserter(tmp_vec));
	merge(make_move_iterator(tmp_vec.begin()), make_move_iterator(tmp_vec.end()), make_move_iterator(middle_2), make_move_iterator(end), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
