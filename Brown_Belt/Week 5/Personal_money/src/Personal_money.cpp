#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

class Date{
private:
	int day_;
	int month_;
	int year_;
public:
	Date():day_(1),month_(1),year_(2000){};
	friend istream& operator>>(istream& stream, Date& date_to_write);
	time_t AsTimestamp() const;
};

istream& operator>> (istream& stream, Date& date_to_write){
	char first_symbol, second_symbol;
	stream >> date_to_write.year_ >> first_symbol >> date_to_write.month_ >> second_symbol >> date_to_write.day_;
	return stream;
}


time_t Date::AsTimestamp() const {
  std::tm t;
  t.tm_sec   = 0;
  t.tm_min   = 0;
  t.tm_hour  = 0;
  t.tm_mday  = day_;
  t.tm_mon   = month_ - 1;
  t.tm_year  = year_ - 1900;
  t.tm_isdst = 0;
  return mktime(&t);
}

class Budget{
private:
	vector<double> dates;
	double tax_coeff = 0.87;
	constexpr static int SECONDS_IN_DAY = 60 * 60 * 24;
public:
	void SetTaxCoeff(double tax){
		tax_coeff = tax;
	}
	void Earn(const Date& date_from, const Date& date_to, size_t value){
		double earned_per_day = value / static_cast<double>(ComputeDaysDiff(date_from, date_to) + 1);
		//cout << "From - to: " << (dates.begin() + date_from.AsTimestamp() / SECONDS_IN_DAY) - (dates.begin() + date_to.AsTimestamp() / SECONDS_IN_DAY) << endl;
		for_each(dates.begin() + date_from.AsTimestamp() / SECONDS_IN_DAY,
				dates.begin() + 1 + date_to.AsTimestamp() / SECONDS_IN_DAY,
				[earned_per_day](double& curr){
			curr += earned_per_day;
		});
	}
	double ComputeIncome(const Date& date_from, const Date& date_to){
		return accumulate(dates.begin() + date_from.AsTimestamp() / SECONDS_IN_DAY,
				dates.begin() + 1 + date_to.AsTimestamp() / SECONDS_IN_DAY, 0.0);
	}
	void PayTax(const Date& date_from, const Date& date_to){
		for_each(dates.begin() + date_from.AsTimestamp() / SECONDS_IN_DAY,
				dates.begin() + 1 + date_to.AsTimestamp() / SECONDS_IN_DAY, [this](double& curr){
			curr*= this->tax_coeff;
		});
	}
	const vector<double>& GetInfoPerDate() const{
		return dates;
	}
	Budget() : dates(48000, 0.0){};
	static int ComputeDaysDiff(const Date& date_from, const Date& date_to){
		const time_t timestamp_to = date_to.AsTimestamp();
		const time_t timestamp_from = date_from.AsTimestamp();
		//static const int SECONDS_IN_DAY = 60 * 60 * 24;
		return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
	}
};


int main() {
	int Q;
	Budget personal_budget;
//	Date from, to;
//	size_t val;
//	stringstream str("2000-01-02 2000-01-06 20\n2000-01-01 2001-01-01\n2000-01-02 2000-01-03\n2000-01-01 2001-01-01");
//	str >> from >> to >> val;
//	personal_budget.Earn(from, to, val);
//	str >> from >> to;
//	cout << personal_budget.ComputeIncome(from, to) << endl;
//	str >> from >> to;
//	personal_budget.PayTax(from, to);
//	str >> from >> to;
//	cout << personal_budget.ComputeIncome(from, to) << endl;
	cin >> Q;
	string operation;
	Date from, to;
	for(;Q > 0; Q--){
		cin >> operation >> from >> to;
		//cout << operation << endl;
//		cin >> from;
//		cout << from.AsTimestamp() << endl;
////		cin >> to;
//		cout << to.AsTimestamp() << endl;
		if(operation == "Earn"){
			int value = 0;
			cin >> value;
			personal_budget.Earn(from, to, value);
		}
		else if(operation == "ComputeIncome"){
			//cout << std::setprecision(25);
			cout.precision(25);
			cout << personal_budget.ComputeIncome(from, to) << endl;
		}
		else if(operation == "PayTax"){
			personal_budget.PayTax(from, to);
		}
		else{
			cerr << "Undefined command" << endl;
		}
	}
	return 0;
}
