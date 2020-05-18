#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0): size(a_size), data(arr.data()), end_(data + size){
	  if(a_size > capacity){
		  throw(invalid_argument(""));
	  }
  }

  T& operator[](size_t index){
	  return data[index];
  }
  const T& operator[](size_t index) const{
	  return data[index];
  }

  T* begin(){
	  return data;
  }
  T* end(){
	  return end_;
  }
  const T* begin() const{
	  return data;
  }
  const T* end() const{
	  return end_;
  }

  size_t Size() const{
	  return size;
  }
  size_t Capacity() const{
	  return N;
  }

  void PushBack(const T& value){
	  if(size == capacity){
		  throw(overflow_error(""));
	  }
	  *(data + size) = value;
	  ++size;
  }
  T PopBack(){
	  if(size == 0){
		  throw(underflow_error(""));
	  }
	  --size;
	  return *(data + size);
  }

private:
  size_t capacity = N;
  array<T, N> arr;
  size_t size;
  T* data;
  T* end_;

};
