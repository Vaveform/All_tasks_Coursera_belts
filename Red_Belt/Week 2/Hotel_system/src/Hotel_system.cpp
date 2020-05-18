#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <cstdint>
#include <unordered_map>

using namespace std;


//����� � ������ ������������ queue
class Book_System{
    public:
    int rooms(const string& hotel_name){
        return rooms_in_hotel[hotel_name];
    }
    int clients(const string& hotel_name){
        return id_in_hotel[hotel_name].size();
    }
    void book(const int64_t& time, const string& hotel_name,
    const int& client_id, const int& room_count){
        auto event = make_tuple(time, hotel_name, client_id, room_count);
        Adjust(event);
        events.push_back(event);
        rooms_in_hotel[get<1>(event)] += get<3>(event);
        rooms_of_clients[get<2>(event)] += get<3>(event);
        id_in_hotel[get<1>(event)].insert(get<2>(event));
    }
    private:
    deque<tuple<int64_t, string, int, int>> events;
    unordered_map<string, int> rooms_in_hotel;
    unordered_map<string, set<int>> id_in_hotel;
    unordered_map<int, int> rooms_of_clients;
    void Adjust(tuple<int64_t, string, int, int> request){
        while(!events.empty() && get<0>(events.front()) <= get<0>(request) - 86400){
            rooms_in_hotel[get<1>(events.front())] -= get<3>(events.front());
            int& ref = rooms_of_clients[get<2>(events.front())];
            ref -= get<3>(events.front());
            if(ref == 0){
                id_in_hotel[get<1>(events.front())].erase(get<2>(events.front()));
            }
            events.pop_front();
        }
    }
};

int main()
{
  //���� �� ���������� ������ ����� � ������, �� ��������� ����� �������� �������� ���-�� � 2 ����)
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Book_System manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    string hotel_name;
    if (query_type == "ROOMS") {
    	cin >> hotel_name;
        cout << manager.rooms(hotel_name) << "\n";
    } else if (query_type == "CLIENTS") {
    	cin >> hotel_name;
      cout << manager.clients(hotel_name) << "\n";
    }
    else if (query_type == "BOOK"){
        int64_t time;
        int client_id;
        int num_rooms;
        cin >> time;
        cin >> hotel_name;
        cin >> client_id;
        cin >> num_rooms;
        manager.book(time, hotel_name, client_id, num_rooms);
    }
  }


    return 0;
}
