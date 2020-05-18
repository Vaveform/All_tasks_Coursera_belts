#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) {
	  log_line = value;
  }
  void SetLogFile(bool value) {
	  log_file= value;
  }
  void SetLine(int code_line){
	  line = code_line;
  }
  void SetFile(string code_file){
	  file = code_file;
  }

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
  int line;
  string file;
};

void Logger::Log(const string& message)
{
	if(log_line == 0 && log_file == 0){
		os << message << "\n";
	}
	else if(log_line == 1 && log_file == 0){
		os << "Line " << line << " " << message << "\n";
	}
	else if(log_line == 0 && log_file == 1){
		os << file << " " << message << "\n";
	}
	else{
		os << file << ":" << line << " " << message << "\n";
	}
}

#define LOG(logger, message) {                                         \
	logger.SetFile(__FILE__);                                          \
	logger.SetLine(__LINE__);                                          \
	logger.Log(message);                                               \
}

void TestLog() {
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
  return 0;
}
