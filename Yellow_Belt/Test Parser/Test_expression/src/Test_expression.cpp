#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <string>
#include <cstdint>
#include "classes.h"
#include "parse.h"

using namespace std;

// ��������!
// ��� �������� ������� ����� ������������ ������ ����� �� ����� �����,
// � ����� �� ����� ������, �������� � �������� ��������.
// ��� ����, ����� �������, ��� ��������� ������ ���������.

int main() {
  string tokens = "x+5*x-3*3";
  cout << "Enter expression: " << tokens << endl;
//  getline(cin, tokens);
  int x = 0;
  auto node = Parse(tokens.begin(), tokens.end(), x);
  vector<int> nums = {2, 5, 6, 4, 1};
  for(auto const& elem : nums) {
	x = elem;
	cout << "Enter x: " << x << endl;
    cout << "Expression value: " << node->Evaluate() << endl;
  }

  return 0;
}
