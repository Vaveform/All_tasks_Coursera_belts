
#include <iostream>
using namespace std;

class ReversibleString
{
public:
	ReversibleString(const string& new_s)
    {
	    s = new_s;
	}
	ReversibleString()
	{
		s = "";
	}
	void Reverse()
	{
		string tmp;
		string :: iterator it;
		for(it = s.end()-1; it >= s.begin(); it--)   //тут можно вызвать функцию reverse!!!
		{
		    tmp += *it;
		}
		s = tmp;
		tmp.clear();
	}
	string ToString() const
	{
		return s;
	}
private:
    string s;
};


int main()
{
	ReversibleString s("live");
	s.Reverse();
	cout << s.ToString() << endl;

	s.Reverse();
    const ReversibleString& s_ref = s;
	string tmp = s_ref.ToString();
	cout << tmp << endl;

	ReversibleString empty;
	cout << '"' << empty.ToString() << '"' << endl;

	return 0;
}
