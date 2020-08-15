#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
  T* pointer;
public:
  UniquePtr() : pointer(nullptr){};
  UniquePtr(T * ptr) : pointer(ptr){};
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other): pointer(move(other.pointer)){
	  other.pointer = nullptr;
  };
  UniquePtr& operator = (const UniquePtr&) = delete;
  UniquePtr& operator = (nullptr_t){
	  delete pointer;
	  this->pointer = nullptr;
	  return *this;
  };
  UniquePtr& operator = (UniquePtr&& other){
	  if(other.pointer != pointer){
		  delete pointer;
		  this->pointer = move(other.pointer);
		  other.pointer = nullptr;
	  }
	  return *this;
  };
  ~UniquePtr(){
	  delete pointer;
  };

  T& operator * () const{
	  return *pointer;
  };

  T * operator -> () const{
	  return pointer;
  }

  T * Release(){
	  T* tmp = pointer;
	  pointer = nullptr;
	  return tmp;
  }

  void Reset(T * ptr){
	  delete pointer;
	  pointer = ptr;
  }

  void Swap(UniquePtr& other){
	  swap(pointer, other.pointer);
  }

  T * Get() const{
	  return pointer;
  }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
