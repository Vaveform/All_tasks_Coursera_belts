#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define macro3(code_line) variable_on_line_##code_line
#define macro1(code_line) macro3(code_line)
#define UNIQ_ID macro1(__LINE__)

int main() {
	int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}
