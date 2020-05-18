#include "test_runner.h"

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

template<typename T> class Table{
private:
	vector<vector<T>> table;
public:
	Table(size_t nums_of_rows, size_t nums_of_columns){
		Resize(nums_of_rows, nums_of_columns);
	}
	void Resize(size_t nums_of_rows, size_t nums_of_columns){
		table.resize(nums_of_rows);
		for(auto& elem: table){
			elem.resize(nums_of_columns);
		}
	}
	pair<size_t, size_t> Size() const {
		return make_pair(table.size(), table.size() == 0 ? 0 : table[0].size());
	}
	const vector<T>& operator[](size_t row_number) const {
		return table[row_number];
	}
	vector<T>& operator[](size_t row_number){
			return table[row_number];
	}
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
