#include "test_runner.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <utility>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {

public:
  using BucketList = forward_list<Type>;

public:
  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  ) : Table(num_buckets), hash_func(hasher) {}

  void Add(const Type& value){
	  size_t index = hash_func(value) % Table.size();
	  auto finded = find(Table[index].begin(), Table[index].end(), value);
	  if(finded == Table[index].end()){
		  Table[index].push_front(value);
	  }
  }
  bool Has(const Type& value) const{
	  size_t index = hash_func(value) % Table.size();
	  auto finded = find(Table[index].begin(), Table[index].end(), value);
	  return finded == Table[index].end() ? false : true;
  }
  void Erase(const Type& value){
	  size_t index = hash_func(value) % Table.size();
	  Table[index].remove(value);

  }
  const BucketList& GetBucket(const Type& value) const{
	  return Table[hash_func(value) % Table.size()];
  }
private:
  vector<BucketList> Table;
  Hasher hash_func;
};

struct IntHasher {
  size_t operator()(int value) const {
    return value;
  }
};


struct TestValue {
  int value;

  bool operator==(TestValue other) const {
    return value / 2 == other.value / 2;
  }
};

struct TestValueHasher {
  size_t operator()(TestValue value) const {
    return value.value / 2;
  }
};

void TestSmoke() {
  HashSet<int, IntHasher> hash_set(2);
  hash_set.Add(3);
  hash_set.Add(4);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Erase(3);

  ASSERT(!hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Add(3);
  hash_set.Add(5);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(hash_set.Has(5));
}

void TestEmpty() {
  HashSet<int, IntHasher> hash_set(10);
  for (int value = 0; value < 10000; ++value) {
    ASSERT(!hash_set.Has(value));
  }
}

void TestIdempotency() {
  HashSet<int, IntHasher> hash_set(10);
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
  HashSet<TestValue, TestValueHasher> hash_set(10);
  hash_set.Add(TestValue{2});
  hash_set.Add(TestValue{3});

  ASSERT(hash_set.Has(TestValue{2}));
  ASSERT(hash_set.Has(TestValue{3}));

  const auto& bucket = hash_set.GetBucket(TestValue{2});
  const auto& three_bucket = hash_set.GetBucket(TestValue{3});
  ASSERT_EQUAL(&bucket, &three_bucket);

  ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
  ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestIdempotency);
  RUN_TEST(tr, TestEquivalence);
  return 0;
}
