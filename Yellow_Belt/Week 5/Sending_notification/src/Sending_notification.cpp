#include <iostream>
#include <string>
#include <memory>

using namespace std;

void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */
class INotifier{
public:
	virtual void Notify(const string& _message) = 0;
};

class SmsNotifier : public INotifier{
public:
	SmsNotifier(const string& number) :
		telephone_number(number) {}
	void Notify (const string& _message) override{
		SendSms(telephone_number, _message);
	}
	const string telephone_number;
};

class EmailNotifier: public INotifier{
public:
	EmailNotifier(const string& new_email) :
		email_address(new_email) {}
	void Notify(const string& _message) override{
		SendEmail(email_address, _message);
	}
	const string email_address;
};

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}
