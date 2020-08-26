#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : pages_by_user_(MAX_PAGES_ + 1, 0),
		users_by_page_(MAX_USER_COUNT_ + 1, -1) {};

  void Read(int user_id, int page_count) {
	  if(users_by_page_[user_id] == -1){
		  AddUser(user_id);
	  }
	  ReplaceUser(users_by_page_[user_id], page_count);
  }

  double Cheer(int user_id) const {
    if (users_by_page_[user_id] == -1) {
      return 0;
    }
    if (this->GetUserCount() == 1) {
      return 1;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return accumulate(pages_by_user_.begin(), pages_by_user_.begin() + users_by_page_[user_id], 0)
    		* 1.0 / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGES_ = 1'000;

  int user_count = 0;

  vector<int> pages_by_user_;   // Вектор страниц, где индексы - номера страниц
  // , а значения количество пользователей на данной странице.
  vector<int> users_by_page_;   // Вектор пользователей: индексы - номера пользователей, а значения
  // - номер страницы, на которой данный пользователь остановился.

  int GetUserCount() const {
	  return user_count;
  }
  void AddUser(int user_id) {
	  users_by_page_[user_id] = 0;
	  pages_by_user_[users_by_page_[user_id]]++;
	  user_count++;
  }
  void ReplaceUser(int& old_position, int step) {
	  pages_by_user_[old_position]--;
	  old_position = step;
	  int new_position = old_position;
	  pages_by_user_[new_position]++;
  }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
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
