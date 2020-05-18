
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

void PrintSet(const set<string>& w)
{
	for(const auto& elem: w)
	{
		cout << elem << " ";
	}
	cout << endl;
}

void PrintDict(const map<string, set<string>>& dict)
{
	for(const auto& item: dict)
	{
		cout << item.first << ":";
		PrintSet(item.second);
	}
}

void add(map<string, set<string>>& to_be_added, string word1, string word2)
{
	to_be_added[word1].insert(word2);
	to_be_added[word2].insert(word1);
}
void count(map<string, set<string>>& to_be_counted, string word)
{
	cout << to_be_counted[word].size() << endl;
}

void check(map<string, set<string>>& to_be_checked, string word1, string word2)
{
	if(to_be_checked[word1].find(word2) != to_be_checked[word1].end())
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}

int main()
{
	map<string, set<string>> dict;
	int num_of_operation;
	string operation;
	cin >> num_of_operation;
	while(num_of_operation > 0)
	{
		cin >> operation;
		if(operation == "ADD")
		{
			string word1, word2;
			cin >> word1 >> word2;
			add(dict, word1, word2);
		}
		else if(operation == "COUNT")
		{
			string word;
			cin >> word;
			count(dict, word);
		}
		else
		{
			string word1, word2;
			cin >> word1 >> word2;
			check(dict, word1, word2);
		}
		num_of_operation--;
	}
	return 0;
}
