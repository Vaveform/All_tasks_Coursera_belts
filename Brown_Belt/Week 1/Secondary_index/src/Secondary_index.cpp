#include "test_runner.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <forward_list>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};



// Р РµР°Р»РёР·СѓР№С‚Рµ СЌС‚РѕС‚ РєР»Р°СЃСЃ
class Database {
public:
  bool Put(const Record& record){
	  if(id_to_record.count(record.id) == 0){
		  auto iterator_to_inserted = id_to_record.emplace(record.id, record);
		  timestamp_to_iterator.emplace(record.timestamp, &(*iterator_to_inserted.first).second);
		  karma_to_iterator.emplace(record.karma, &(*iterator_to_inserted.first).second);
		  name_to_iterator.emplace(record.user, &(*iterator_to_inserted.first).second);
		  return true;
	  }
	  return false;
  }
  const Record* GetById(const string& id) const{
	  if(id_to_record.count(id) == 0){
		  return nullptr;
	  }
	  return &((*id_to_record.find(id)).second);
  }
  bool Erase(const string& id){
	  if(id_to_record.count(id) != 0){
		  auto Equal_range = timestamp_to_iterator.equal_range(id_to_record[id].timestamp);
		  timestamp_to_iterator.erase(Find_In_Equal_Range(Equal_range.first, Equal_range.second, id));
		  Equal_range = karma_to_iterator.equal_range(id_to_record[id].karma);
		  karma_to_iterator.erase(Find_In_Equal_Range(Equal_range.first, Equal_range.second, id));
		  auto Equal_range_Users = name_to_iterator.equal_range(id_to_record[id].user);
		  name_to_iterator.erase(Find_In_Equal_Range(Equal_range_Users.first, Equal_range_Users.second, id));
		  id_to_record.erase(id);
		  return true;
	  }
	  return false;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
	  auto iterator_low = timestamp_to_iterator.lower_bound(low);
	  for(auto it = iterator_low; it != timestamp_to_iterator.end(); it++){
		  if(!callback(*(it->second)) && it->first > high){
			  break;
		  }
	  }

  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
	  auto iterator_low = karma_to_iterator.lower_bound(low);
	  for(auto it = iterator_low; it != karma_to_iterator.end(); it++){
		  if(!callback(*(it->second)) && it->first > high){
			  break;
		  }
	  }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
	  auto iterator_to_equal = name_to_iterator.equal_range(user);
	  for(auto it = iterator_to_equal.first; it != iterator_to_equal.second;it++){
		  if(user == it->first){
			  if(!callback(*(it->second))){
				  break;
			  }
		  }
		  else{
			  break;
		  }
	  }

  }
private:
  unordered_map<string, Record> id_to_record;
  multimap<int, Record*> timestamp_to_iterator;
  multimap<int, Record*> karma_to_iterator;
  multimap<string, Record*> name_to_iterator;

  template <typename Iterator>
  Iterator Find_In_Equal_Range(Iterator begin, Iterator end, const string& id){
	  return find_if(begin, end, [id](auto& pair_of_multimap){
		  return (*pair_of_multimap.second).id == id;
	  });
  }

};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
