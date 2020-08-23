#include "Common.h"

#include <unordered_map>
#include <list>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) : capacity(settings.max_memory), unpacker(books_unpacker) {};

  struct SizeOfBook{
	  string name;
	  size_t book_size;
  };

  BookPtr GetBook(const string& book_name) override {
	lock_guard<mutex> stop(critical);
	auto finded_iterator = hash_table.find(book_name);
	if(finded_iterator == hash_table.end())
	{
		shared_ptr<IBook> book = unpacker->UnpackBook(book_name);
		while(capacity - size_of_contents < book->GetContent().size() && size_of_contents > 0){
			hash_table.erase(states.front()->GetName());
			size_of_contents -= states.front()->GetContent().size();
			states.pop_front();
		}
		if(capacity - size_of_contents >= book->GetContent().size()){
			states.push_back(book);
			size_of_contents += states.back()->GetContent().size();
			hash_table[book_name] = prev(states.end(), 1);
			return book;
		}
		return nullptr;
	}
	else{
		if(states.back()->GetName() != finded_iterator->first){
			states.push_back(*finded_iterator->second);
			states.erase(finded_iterator->second);
			finded_iterator->second = prev(states.end(), 1);
		}
	}
	return *finded_iterator->second;
  }
private:
  mutex critical;
  size_t capacity;
  size_t size_of_contents = 0;
  shared_ptr<IBooksUnpacker> unpacker;
  unordered_map<string, list<shared_ptr<IBook>>::iterator> hash_table;
  list<shared_ptr<IBook>> states;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  return make_unique<LruCache>(books_unpacker, settings);
}
