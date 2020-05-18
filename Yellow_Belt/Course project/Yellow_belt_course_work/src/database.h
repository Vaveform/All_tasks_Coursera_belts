#pragma once

#include "date.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <stdexcept>
#include <exception>
#include <algorithm>

using namespace std;

struct Entry{
private:
	Date date;
	string activity;
public:
	Entry(const Date& d, const string& e);
	Date GetDate() const;
	string GetEvent() const;
	friend ostream& operator<<(ostream& stream, const Entry& pair);
	friend bool operator!=(const Entry& lhd, const Entry& rhd);
};

ostream& operator<<(ostream& stream, const Entry& pair);
bool operator!=(const Entry& lhd, const Entry& rhd);

class Database
{
private:
	map<Date, vector<string>> data;
	map<Date, set<string>> repeated;
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& output) const;
	Entry Last(const Date& date) const;
	template <typename Func>
	vector<Entry> FindIf(Func predicate) const
	{
		vector<Entry> result;
		auto begin_key = data.begin();
		auto begin_vec = data.begin()->second.begin();
		while(begin_key != data.end())
		{
			while(begin_vec != begin_key->second.end())
			{
				begin_vec = find_if(begin_vec, begin_key->second.end(), [begin_key, predicate](const string& e){
					return predicate(begin_key->first, e);
				});
				if(begin_vec != begin_key->second.end())
				{
					Entry tmp(begin_key->first, *begin_vec);
					result.push_back(tmp);
					begin_vec++;
				}
			}
			if(begin_key != data.end()){
				begin_key++;
				begin_vec = begin_key->second.begin();
			}
		}
		return result;
	}
	template <typename Func>
	int RemoveIf(Func predicate)
	{
		int result = 0;
		vector<Date> deleted_date;
		repeated.clear();
		for(auto it = data.begin(); it != data.end(); ++it)
		{
			result += it->second.size();
			auto pointer = stable_partition(it->second.begin(), it->second.end(), [it, predicate](const string& e){
				return !predicate(it->first, e);
			});
			it->second.erase(pointer, it->second.end());
			result -= it->second.size();
			repeated[it->first].insert(it->second.begin(), pointer);
			if(repeated.at(it->first).size() == 0)
			{
				deleted_date.push_back(it->first);
			}
		}
		for(auto it = deleted_date.begin(); it != deleted_date.end(); ++it)
		{
			data.erase(*it);
			repeated.erase(*it);
		}
		deleted_date.clear();
		return result;
	}
};
