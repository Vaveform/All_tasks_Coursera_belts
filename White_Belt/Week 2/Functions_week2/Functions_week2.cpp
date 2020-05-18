#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

int Factorial(int num)
{
	if(num <= 1)
	{
		return 1;
	}
	return num * Factorial(num - 1);
}

void UpdateIfGreater(int first, int &second)
{
	if(first > second)
	{
		second = first;
	}
}

void MoveStrings(vector<string>& source, vector<string>& destination)
{
	for(auto s: source)
	{
		destination.push_back(s);
	}
	source.clear();
}

void Reverse(vector<int>& v)
{
	for(int i = 0; i < round(v.size() / 2); ++i)
	{
		swap(v[i], v[v.size() - 1 - i]);
	}
}

vector<int> Reversed(const vector<int>& v)
{
	vector<int> result;
	for(int i = v.size() - 1; i >= 0; --i)
	{
		result.push_back(v[i]);
	}
	return result;
}

bool IsPalindrom(string w)
{
	for(int i = 0; i < round(w.length() / 2); ++i)
	{
		if(w[i] != w[w.length() - 1 - i])
		{
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> result;
	for(int i = 0; i < words.size(); ++i)
	{
		if(IsPalindrom(words[i]) && words[i].length() >= minLength)
		{
			result.push_back(words[i]);
		}
	}
	return result;
}


int main()
{
	int n;
	cin >> n;
	vector<int> tempretures(n);
	int sum = 0;
	for(int t : tempretures)
	{
		cin >> t;
		sum+= t;
	}
	cout << sum << endl;
	return 0;
}
