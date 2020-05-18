#include <iostream>
#include <map>
#include <exception>
using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& dict, Key key)
{
	if(dict.find(key) != dict.end()){
		Value& ref = dict.at(key);
		return ref;
	}
	else{
		throw runtime_error("Not found");
	}
}

int main() {
	return 0;
}
