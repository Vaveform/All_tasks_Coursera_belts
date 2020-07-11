#pragma once

#include <algorithm>
#include <vector>
using namespace std;

template <typename It>
class IteratorRange {
public:
  IteratorRange(It first, It last) : first(first), last(last) {
  }

  It begin() const {
    return first;
  }

  It end() const {
    return last;
  }

  size_t size() const {
    return last - first;
  }

private:
  It first, last;
};

template <typename Container>
auto Head(Container& c, int top) {
  return IteratorRange(begin(c), begin(c) + min<size_t>(max(top, 0), c.size()));
}


template <typename Iter>
class IteratorRangeImp{
private:
	Iter first;
	Iter last;
	size_t SIZE_PAGE;
public:
	IteratorRangeImp(Iter f, Iter l, size_t s): first(f), last(l), SIZE_PAGE(s){};
	Iter begin() const{
		return first;
	}
	Iter end() const{
		return last;
	}
	size_t size() const{
		return SIZE_PAGE;
	}
};

template <typename Iterator>
class Paginator {
private:
	vector<IteratorRangeImp<Iterator>> Values;
	size_t SIZE;
public:
	Paginator(Iterator f, Iterator l, size_t s){
		//cout << l - f << endl;
		auto start_page = f;
		auto end_page = f;
		vector<IteratorRangeImp<Iterator>> Pages;
		while(end_page != l){
			end_page = next(start_page, min(s, size_t(l - start_page)));
			Pages.push_back(IteratorRangeImp{start_page, end_page, size_t(end_page - start_page)});
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
