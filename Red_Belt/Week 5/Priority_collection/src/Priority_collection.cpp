#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
	  Id indentificator = values.size();
	  priority_id.insert(make_pair(0, indentificator));
	  values[indentificator] = make_pair(move(object), 0);
	  return indentificator;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
	  vector<Id> indentificators;
	  for(auto it = range_begin; it != range_end; it++){
		  indentificators.push_back(Add(move(*it)));
	  }
	  move(indentificators.begin(), indentificators.end(), ids_begin);
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
	  return values.find(id) == values.end() ? false : true;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const{
	  return values.find(id)->second.first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id){
	  // Поднимаем приоритет на единицу у элемента с индентификатором id
	  auto iterator_to_element = values.find(id);
	  iterator_to_element->second.second++;
	  priority_id.erase(make_pair(iterator_to_element->second.second - 1, id));
	  priority_id.insert(make_pair(iterator_to_element->second.second, id));
  }
  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
	  auto iterator_to_max_value = values.find(priority_id.rbegin()->second);
	  return {iterator_to_max_value->second.first, iterator_to_max_value->second.second};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
	  auto iterator_to_max = prev(priority_id.end(), 1);
	  auto iterator_to_max_value = values.find(iterator_to_max->second);
	  auto res_pair = make_pair(move(iterator_to_max_value->second.first), iterator_to_max_value->second.second);
	  priority_id.erase(iterator_to_max);
	  values.erase(iterator_to_max_value);
	  return res_pair;
  }

private:
  set<pair<int, Id>> priority_id;
  map<Id, pair<T, int>> values;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

void TestRange(){
	PriorityCollection<StringNonCopyable> strings;
	vector<StringNonCopyable> elements;
	elements.push_back({"red"});
	elements.push_back({"green"});
	elements.push_back({"white"});
	elements.push_back({"blue"});
	vector<int> results(4);
	strings.Add(elements.begin(), elements.end(), results.begin());
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "blue");
		ASSERT_EQUAL(item.second, 0);
	  }
	  {
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	  }
	  {
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "green");
		ASSERT_EQUAL(item.second, 0);
	  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  RUN_TEST(tr, TestRange);
  return 0;
}
