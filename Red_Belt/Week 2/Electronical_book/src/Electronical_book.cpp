#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <cstdint>

using namespace std;

class ReadingManager {
public:
	ReadingManager(): id_page_counts(MAX_USERS + 1, 0), tracking_users(MAX_PAGES + 1, vector<int>{}) {};
    void Read(int user_id, int page_count) {
    	int current_num_of_pages = id_page_counts[user_id];  // O(1)
    	id_page_counts[user_id] = page_count;        // O(1)
    	for(uint16_t i = current_num_of_pages + 1; i <= page_count; i++){        // � ������ ������ 1000 * 100000 �������� - �� ����������� CPU - 1 �������.
    		// ����� ������� � ������������ ������ ���������� - �� �������.
    		// ������������� �������� � ��� �������� ������ ������ ������������ �������� ������ � ������� ������� � �������������� �� ���������.
    		tracking_users[i].push_back(user_id);
    	}
    }

    double Cheer(int user_id) const {
    	size_t num_of_page = id_page_counts[user_id];
    	// ��� ������������, �������� ������ - ��� ���������
    	// ��������� ������ ��������
		size_t num_of_existing_users = tracking_users[1].size();
    	if(num_of_page == 0){
			return 0.0;
		}
		else if(num_of_existing_users == 1){
			// �����, ����� ������, ��� ������������ ������ ���� - ����� ������
			// ����� ������� ��� �������� 1 (��� ������ �������� - ������ ��������� �������������)
			return 1.0;
		}
    	// ������ �� ������� ������� ������� ������� �������� �������� ������������.
    	// ��������� �������� ��������, ��������� � ������� ��������,
		// ���������� ��� ������ �������� ��������� ������������� �������
		// ��������� �������� ��������. ����� ������ ������� ��� ���� �������� -
    	// ��� ���������� ������������� �����������
    	// ��������� ����� �������(������ �� ������) ��� �����.
    	// ����� ������ ������� ������������� ��������� ������ ����� ����� ���� ������
		// �� ������� ���������� �� ������ ��������
		double result = ((num_of_existing_users - tracking_users[num_of_page].size()) * 1.0) / (1.0 * (num_of_existing_users - 1));
		return result;
    }

private:
  static const uint32_t MAX_USERS = 100'000;
  static const uint16_t MAX_PAGES = 1000;

  vector<int> id_page_counts;
  vector<vector<int>> tracking_users;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
