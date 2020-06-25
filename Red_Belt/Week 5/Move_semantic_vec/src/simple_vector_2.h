#include <cstdint>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size): data(new T[size]), SIZE(size), CAPACITY(size){};
  SimpleVector(SimpleVector&& other);

  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);
  void PushBack(T&& value);

private:
  size_t SIZE = 0;
  size_t CAPACITY = 0;
  T* data = nullptr;
};

template<typename T>
SimpleVector<T>::SimpleVector(SimpleVector&& other) : data(other.data), SIZE(other.Capacity()), CAPACITY(other.Capacity()){
	other.data = nullptr;
	other.CAPACITY = other.SIZE = 0;
}

template<typename T>
SimpleVector<T>::~SimpleVector(){
	delete[] data;
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index){
	return data[index];
}

template<typename T>
T* SimpleVector<T>::begin(){
	return data;
}

template<typename T>
T* SimpleVector<T>::end(){
	return data + SIZE;
}

template<typename T>
const T* SimpleVector<T>::begin() const{
	return data;
}

template<typename T>
const T* SimpleVector<T>::end() const{
	return data + SIZE;
}

template<typename T>
size_t SimpleVector<T>::Size() const{
	return SIZE;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const{
	return CAPACITY;
}


template<typename T>
void SimpleVector<T>::PushBack(T&& value){
	if(Size() == Capacity()){
	  size_t cap = Size() == 0 ? 1 : 2 * Capacity();
	  T* new_data = new T[cap];
	  move(data, data + SIZE, new_data);
	  delete[] data;
	  CAPACITY = cap;
	  data = new_data;
    }
	data[SIZE++] = move(value);
}


template<typename T>
void SimpleVector<T>::PushBack(const T& value){
	if(Size() == Capacity()){
	  size_t cap = Size() == 0 ? 1 : 2 * Capacity();
	  T* new_data = new T[cap];
	  copy(data, data + SIZE, new_data);
	  delete[] data;
	  CAPACITY = cap;
	  data = new_data;
    }
	data[SIZE++] = value;
}
