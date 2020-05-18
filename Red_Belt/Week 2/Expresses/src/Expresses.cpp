#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
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
    int result = abs(start - finish); // O(1)
    if (reachable_lists_.count(start) < 1) {      // O(log(size of map))
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start);
    auto upper_element = reachable_stations.lower_bound(finish);         // O(log(size of set))
    if(upper_element == reachable_stations.end()){                       // O(1)
    	upper_element = prev(upper_element);                             // O(1)
    }
	auto lower_element = upper_element;
	if(lower_element != reachable_stations.begin()){
		lower_element = prev(lower_element);
	}
	result = min(result, min(abs(*upper_element - finish), abs(*lower_element - finish)));  // O(1)
    return result;
  }
private:
  map<int, set<int>> reachable_lists_;
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
