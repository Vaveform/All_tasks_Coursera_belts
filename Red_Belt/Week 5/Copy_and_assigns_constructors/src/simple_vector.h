#pragma once

#include <cstdlib>
#include <algorithm>

// � еализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() : data(nullptr), in_size(0), capacity(0){
  }
  explicit SimpleVector(size_t size) : data(new T[size]), in_size(size), capacity(size){
  }
  SimpleVector(const SimpleVector& other) : data(new T[other.Size()]),
		  in_size(other.Size()), capacity(other.Capacity()){
	  std::copy(other.begin(), other.end(), begin());
  }
  void operator=(const SimpleVector& other){
	  if(other.Capacity() <= capacity){
		  std::copy(other.begin(), other.end(), begin());
		  in_size = other.Size();
	  }
	  else{
		  SimpleVector<T> tmp = other;
		  std::swap(tmp.data, data);
		  std::swap(tmp.capacity, capacity);
		  std::swap(tmp.in_size, in_size);
	  }
  }
  ~SimpleVector(){
	  delete[] data;
  }

  T& operator[](size_t index){
	  return data[index];
  }

  T* begin(){
	  return data;
  }

  const T* begin() const{
	  return data;
  }

  T* end(){
	  return data + in_size;
  }

  const T* end() const{
	  return data + in_size;
  }

  size_t Size() const{
	  return in_size;
  }
  size_t Capacity() const{
	  return capacity;
  }
  void PushBack(const T& value){
	  if(Size() == Capacity()){
		  size_t cap = Size() == 0 ? 1 : 2 * Capacity();
		  T* new_data = new T[cap];
		  for(size_t i = 0; i < in_size; ++i){
			  new_data[i] = data[i];
		  }
		  new_data[in_size] = value;
		  in_size++;
		  capacity = cap;
		  delete[] data;
		  data = new_data;
	  }
	  else{
		  data[in_size] = value;
		  in_size++;
	  }
  }

private:
  T* data;
  size_t in_size;
  size_t capacity;
};
