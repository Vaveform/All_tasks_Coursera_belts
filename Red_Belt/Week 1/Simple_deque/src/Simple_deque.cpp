#include "test_runner.h"

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;

#define returned_by_index(index)                                   \
		if(index < front.size() && index < Size())                 \
        {                                                          \
			return front[front.size() - index - 1];                \
		}                                                          \
		else if(index >= front.size() && index < Size())           \
        {                                                          \
			return back[index - front.size()];                     \
		}                                                          \
        throw(out_of_range("Out of range"));                       \

#define get_front()                         \
		if(front.empty()){                  \
			return back.front();            \
		}                                   \
		else{                               \
			return front.back();            \
		}                                   \

#define get_back()                          \
		if(back.empty()){                   \
			return front.front();           \
		}                                   \
		else{                               \
			return back.back();             \
		}                                   \


template <typename Type> class Deque{
private:
	vector<Type> back;
	vector<Type> front;
public:
	Deque(){
		back.resize(0);
		front.resize(0);
	}
	void Clear(){
		back.clear();
		front.clear();
	}
	bool Empty() const{
		return back.empty() && front.empty() ? true : false;
	}
	size_t Size() const{
		return back.size() + front.size();
	}
	Type& operator[](size_t index){
		returned_by_index(index)
	}
	const Type& operator[](size_t index) const {
		returned_by_index(index)
	}
	Type& At(size_t index){
		returned_by_index(index)
	}
	const Type& At(size_t index) const{
		returned_by_index(index)
	}
	Type& Front(){
		get_front()
	}
	Type& Back(){
		get_back()
	}
	const Type& Front() const {
		get_front()
	}
	const Type& Back() const{
		get_back()
	}
	void PushFront(Type elem){
		front.push_back(elem);
	}
	void PushBack(Type elem){
		back.push_back(elem);
	}
};

void TestDeque()
{
	Deque<int> deq;
	deq.PushFront(16);
	deq.PushFront(15);
	deq.PushFront(14);
	deq.PushBack(10);
	deq.PushBack(9);
	ASSERT_EQUAL(deq.Empty(), false);
	ASSERT_EQUAL(deq.Size(), 5);
	ASSERT_EQUAL(deq.Front(), 14);
	ASSERT_EQUAL(deq.Back(), 9);
	ASSERT_EQUAL(deq[0], 14);
	ASSERT_EQUAL(deq[4], 9);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}
