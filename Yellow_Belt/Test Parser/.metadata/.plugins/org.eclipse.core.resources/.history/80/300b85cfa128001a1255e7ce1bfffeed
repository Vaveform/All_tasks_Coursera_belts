#include "database.h"

Entry::Entry(const Date& d, const string& e)
{
	date = d;
	activity = e;
}

Date Entry::GetDate() const
{
	return date;
}

string Entry::GetEvent() const
{
	return activity;
}

ostream& operator<<(ostream& stream, const Entry& pair){
	stream << pair.GetDate() << " " << pair.GetEvent();
	return stream;
}

void Database::Add(const Date& date, const string& event)
{
	auto not_exist = repeated[date].insert(event).second;
	if(not_exist){
		data[date].push_back(event);
	}
	else{
		return;
	}
}

void Database::Print(ostream& output) const
{
	for(auto it_dict = data.begin(); it_dict != data.end(); ++it_dict)
	{
		for(auto it_vec = it_dict->second.begin(); it_vec!=it_dict->second.end(); ++it_vec){
			cout << Entry(it_dict->first, *it_vec) << endl;
		}
	}
}

Entry Database::Last(const Date& date) const
{
	if(date < data.begin()->first)
	{
		throw invalid_argument("Event");
	}
	auto last_pair = prev(data.upper_bound(date));
	return Entry(last_pair->first, last_pair->second.back());
}






