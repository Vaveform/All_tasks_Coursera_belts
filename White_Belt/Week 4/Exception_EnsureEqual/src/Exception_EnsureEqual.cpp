
#include <iostream>
#include <exception>
#include <string>
using namespace std;

void EnsureEqual(const string& left, const string& right)
{
	if(left != right)
	{
		string what_error = left + " != " + right;
		throw runtime_error(what_error);
	}
}

int main()
{
	try {
	    EnsureEqual("C++ White", "C++ Green");
	    EnsureEqual("C++ White", "C++ Yellow");
	  } catch (runtime_error& e) {
	    cout << e.what() << endl;
	  }
	return 0;
}
