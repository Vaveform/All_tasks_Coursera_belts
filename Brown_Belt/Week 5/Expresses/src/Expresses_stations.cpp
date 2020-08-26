#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
	auto nearest_iterator = reachable_stations.lower_bound(finish);
	// Последовательный перебор if-ами верхнего(или равного) значения от искомого
	// А затем нижнего значения - нужно найти число в контейнере наиболее близкое к finish
	// То есть из трех значений нужно найти минимальное
	if(nearest_iterator != reachable_stations.end()){
		// Здесь между верхним и abs(finish - start)
		result = min(result, abs(finish - *nearest_iterator));
	}
	// Если nearest_iterator == reachable_stations.begin() - то prev вернёт
	// reachable_stations.end()
	if(nearest_iterator != reachable_stations.begin()){
		result = min(result, abs(finish - *prev(nearest_iterator)));
	}
    return result;
  }
private:
  unordered_map<int, set<int>> reachable_lists_;
};


int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }
  return 0;
}
