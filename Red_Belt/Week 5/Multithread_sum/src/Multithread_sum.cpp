#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <future>
#include "profile.h"

using namespace std;

static const size_t row_per_thread = 2000;

// � еализуйте шаблон класса Paginator
template <typename It>
class IteratorRange{
private:
	It first;
	It last;
	size_t SIZE_PAGE;
public:
	IteratorRange(It f, It l, size_t s): first(f), last(l), SIZE_PAGE(s){};
	It begin() const{
		return first;
	}
	It end() const{
		return last;
	}
	size_t size() const{
		return SIZE_PAGE;
	}
};

template <typename Iterator>
class Paginator {
private:
	vector<IteratorRange<Iterator>> Values;
	size_t SIZE;
public:
	Paginator(Iterator f, Iterator l, size_t s){
		//cout << l - f << endl;
		auto start_page = f;
		auto end_page = f;
		vector<IteratorRange<Iterator>> Pages;
		while(end_page != l){
			end_page = next(start_page, min(s, size_t(l - start_page)));
			Pages.push_back(IteratorRange{start_page, end_page, size_t(end_page - start_page)});
			start_page = end_page;
		}
		Values = Pages;
		SIZE = Pages.size();
		//cout << SIZE << endl;
	};
	auto begin() const
	{
		return Values.begin();
	}
	auto end() const
	{
		return Values.end();
	}
	size_t size() const {
		return size_t(end() - begin());
	}
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator{c.begin(), c.end(), page_size};
}

template <typename ConteinerOfVectors>
void GenerateSingleThread(ConteinerOfVectors& result,
		size_t first_row,
		size_t column_size){
	for(auto& row : result){
		row.reserve(column_size);
		for(size_t column = 0; column < column_size; column++){
			row.push_back(first_row + column);
		}
		++first_row;
	}
}

vector<vector<int>> GenerateSingleThread(size_t size){
	vector<vector<int>> result(size);
	GenerateSingleThread(result, 0, size);
	return result;
}

// Page_size - ������ ��������� ��� ������ ������
vector<vector<int>> GenerateMultiThread(size_t size, size_t page_size){
	vector<vector<int>> result(size);
	vector<future<void>> futures;
	size_t first_row = 0;
	for(auto page : Paginate(result, page_size)){
		futures.push_back(
				async([page, first_row, size]{
			GenerateSingleThread(page, first_row, size);
		})
		);
		first_row += page_size;
	}
	return result;
}

template <typename ConteinerOfVectors>
int64_t SumSingleThread(const ConteinerOfVectors& matrix){
	int64_t result = 0;
	for(const auto& row : matrix){
		result = accumulate(row.begin(), row.end(), result);
	}
	return result;
}

template <typename ConteinerOfVectors>
int64_t CalculateMatrixSum(const ConteinerOfVectors& matrix) {
	vector<future<int64_t>> futures;
	int64_t result = 0;
	for(auto page : Paginate(matrix, row_per_thread)){
		futures.push_back(async([page]{ return SumSingleThread(page);}));
	}
	for(auto& fut : futures){
		result += fut.get();
	}
	return result;
}


int main(){
	return 0;
}
