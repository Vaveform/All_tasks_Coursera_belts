#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const{
	  if(captured){
		  captured->Process(move(email));
	  }
	  return;
  }

public:
  void SetNext(unique_ptr<Worker> next){
	  captured = move(next);
  }
  // Типа next, как у обычного односвязанного списка
  unique_ptr<Worker> captured = unique_ptr<Worker>(nullptr);
};


class Reader : public Worker {
public:
  Reader(istream& input) : input_(input){};
  void Process(unique_ptr<Email> email) {};
  virtual void Run() {
	  unique_ptr<Email> email;
	  string from, to, body;
	  while(input_){
		  getline(input_, from);
		  getline(input_, to);
		  getline(input_, body);
		  email = make_unique<Email>();
		  email->from = move(from);
		  email->to = move(to);
		  email->body = move(body);
		  if(!(!input_ && (email->from.empty() || email->to.empty() || email->body.empty()))){
			  PassOn(move(email));
		  }
	  }
  }
private:
  istream& input_;
};


class Filter : public Worker {
public:

  using Function = function<bool(const Email&)>;
  explicit Filter(Function func) : func_(func) {};

public:
  virtual void Process(unique_ptr<Email> email){
	  if(func_(*email.get())){
		  PassOn(move(email));
	  }
  }
private:
  Function func_;
};


class Copier : public Worker {
public:
  explicit Copier(string address) : address_(address){};
  virtual void Process(unique_ptr<Email> email){
	  if(email->to != address_){
		  string from_ = email->from;
		  string body_ = email->body;
		  PassOn(move(email));
		  PassOn(make_unique<Email>(Email{move(from_), address_, move(body_)}));
	  }
	  else{
		  PassOn(move(email));
	  }
  }
public:
  string address_;
};


class Sender : public Worker {
public:
  explicit Sender(ostream& out_stream) : out(out_stream){};
  virtual void Process(unique_ptr<Email> email){
	  out << email->from << endl;
	  out << email->to << endl;
	  out << email->body << endl;
	  PassOn(move(email));
  }
private:
  ostream& out;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in) : head(make_unique<Reader>(in)), ptr_next(head.get()){};

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
	  ptr_next->SetNext(move(make_unique<Filter>(filter)));
	  ptr_next = ptr_next->captured.get();
	  return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
	  ptr_next->SetNext(move(make_unique<Copier>(recipient)));
	  ptr_next = ptr_next->captured.get();
	  return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
	  ptr_next->SetNext(move(make_unique<Sender>(out)));
	  ptr_next = ptr_next->captured.get();
	  return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
	  return move(head);
  }
private:
  unique_ptr<Worker> head;
  Worker* ptr_next;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
  //cout << outStream.str() << endl;
  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestSanity);
  string input = (
      "erich@example.com\n"
      "richard@example.com\n"
      "Hello there\n"

      "erich@example.com\n"
      "ralph@example.com\n"
      "Are you sure you pressed the right button?\n"

      "ralph@example.com\n"
      "erich@example.com\n"
      "I do not make mistakes of that kind\n"

	  "exf@example.com\n"
    );
	istringstream inStream(input);
	ostringstream outStream;

	PipelineBuilder builder(inStream);
	builder.Send(outStream);
	auto b = builder.Build();
	b->Run();
	cout << outStream.str() << endl;
  return 0;
}
