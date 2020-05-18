#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
	  T* new_object;
	  if(free.empty())
	  {
		  new_object = new T;
		  employed.insert(new_object);
	  }
	  else
	  {
		  new_object = free.front();
		  free.pop();
		  employed.insert(new_object);
	  }
	  return new_object;
  }
  T* TryAllocate(){
	  if(free.empty()){
		  return nullptr;
	  }
	  else{
		  T* new_object = free.front();
		  free.pop();
		  employed.insert(new_object);
		  return new_object;
	  }
  }

  void Deallocate(T* object){
	  auto finded_object = employed.find(object);
	  if(finded_object != employed.end()){
		  free.push(*finded_object);
		  employed.erase(finded_object);
	  }
	  else{
		  throw invalid_argument("invalid argument");
	  }
  }

  ~ObjectPool(){
	  while(!free.empty()){
		  delete free.front();
		  free.pop();
	  }
	  for(auto elem : employed){
		  delete elem;
	  }
	  employed.erase(employed.begin(), employed.end());
	  cout << employed.size() << endl;
  }

private:
  queue<T*> free;
  set<T*> employed;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
