#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template <typename T>
T Sqr(T x);

template <typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> x);

template <typename V>
vector<V> Sqr(vector<V> vi);

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> dict);

template <typename T>
T Sqr(T x){
	return x * x;
}

template <typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second> p){
	return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename V>
vector<V> Sqr(vector<V> vi){
	vector<V> result;
	for(const auto& elem: vi){
		result.push_back(Sqr(elem));
	}
	return result;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value> dict){
	map<Key, Value> result;
	for(const auto& item: dict){
		result[item.first] = Sqr(item.second);
	}
	return result;
}


int main()
{

	return 0;
}
