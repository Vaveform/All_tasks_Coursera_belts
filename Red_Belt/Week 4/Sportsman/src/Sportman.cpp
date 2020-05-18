#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

class SportsmanCounter{
public:
	void PassSportsman(int id, int before_id){
		// ������ ���� , ��� � �� ��������� ��������,
		// ����� ����������� before_id ��� � �������
		// id_before_add.��� � �������� ��� ������� before_id = 0
		// ����� ������� � �����, � ��� ������ ������ ���������
		// ����� � ���������� ����� ���� � 0
//		auto pos = id_before_add.find(before_id); // �������� �� log(N)
//		if(pos == id_before_add.end()){
//			id_before_add[id] = order.insert(order.end(), id); // log(N)
//		}
//		else{
//			id_before_add[id] = order.insert(pos->second, id); // log(N)
//		}
		// �������� �������� �� O(log(N))
		if(positions[before_id] == order.end()){
			positions[id] = order.insert(order.end(), id);
		}
		else{
			positions[id] = order.insert(positions[before_id], id);
		}
		// �������� �������� �� ����������� ����� O(1), ��������� ����������
		// �� ������� � �������� �������, �� ����� �� ����������� �� ������,
		// ����� ������ �� ���������� �������� 100000
		// � ������ ������ ����� ������������ unordered_map - � ���
		// ������� � ��������� - �� ����������� �����
	}
	friend ostream& operator<< (ostream& out, SportsmanCounter order);
private:
	list<int> order;
//	map<int, list<int>::iterator> id_before_add;
	const size_t sportsmen_nums = 100000;
	vector<list<int>::iterator> positions = {sportsmen_nums + 1, order.end()};
};

ostream& operator<< (ostream& out, SportsmanCounter order){
	for(const auto& elem: order.order){
		cout << elem << " ";
	}
	return out;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
    SportsmanCounter i;
	int query_count;
	cin >> query_count;
	for(int query_id = 0; query_id < query_count; ++query_id){
		int id, before_id;
		cin >> id >> before_id;
		i.PassSportsman(id, before_id);
	}
	cout << i << endl;
	return 0;
}
