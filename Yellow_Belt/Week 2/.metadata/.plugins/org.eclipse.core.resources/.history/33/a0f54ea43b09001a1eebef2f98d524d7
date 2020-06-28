#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int gcd(int a, int b)
{
	int result = b;
	if(a < b)
	{
		swap(a, b);
	}
	while(a % b != 0)
	{
		int tmp = b;
		b = a % b;
		a = tmp;
	}
	swap(result, b);
	return result;
}

class Rational {
public:
    Rational()
    {
    	numerator = 0;
    	denominator = 1;
    }
    Rational(int new_numerator, int new_denominator)
    {
    	Update(new_numerator, new_denominator);
    }

    int Numerator() const {
    	return numerator;
    }

    int Denominator() const {
    	return denominator;
    }
    friend bool operator==(const Rational& lhd, const Rational& rhd);
    friend Rational operator+(const Rational& lhd, const Rational& rhd);
    friend Rational operator-(const Rational& lhd, const Rational& rhd);
    friend Rational operator*(const Rational& lhd, const Rational& rhd);
    friend Rational operator/(const Rational& lhd, const Rational& rhd);
    friend istream& operator>>(istream& stream, Rational& R);
    friend ostream& operator<<(ostream& stream, const Rational& R);
    friend bool operator<(const Rational& lhd, const Rational& rhd);
    friend bool operator>(const Rational& lhd, const Rational& rhd);

private:
    int numerator;
    int denominator;
    void Update(int new_numerator, int new_denominator)
	{
		if(new_numerator == 0)
		{
			numerator = 0;
			denominator = 1;
		}
		else if(new_denominator == 0)
		{
			throw invalid_argument("Invalid argument");
		}
		else if((new_numerator > 0 && new_denominator < 0) || (new_numerator < 0 && new_denominator < 0))
		{
			numerator = ((-1) * new_numerator) / gcd(abs(new_numerator), abs(new_denominator));
			denominator = ((-1) * new_denominator) / gcd(abs(new_numerator), abs(new_denominator));
		}
		else{
			numerator = new_numerator / gcd(abs(new_numerator), abs(new_denominator));
			denominator = new_denominator / gcd(abs(new_numerator), abs(new_denominator));
		}
	}
};

bool operator==(const Rational& lhd, const Rational& rhd)
{
	if(lhd.numerator * rhd.denominator == rhd.numerator * lhd.denominator)
	{
		return true;
	}
	else{
		return false;
	}
}
Rational operator+(const Rational& lhd, const Rational& rhd)
{
	return Rational(lhd.numerator * rhd.denominator + rhd.numerator * lhd.denominator, lhd.denominator*rhd.denominator);
}
Rational operator-(const Rational& lhd, const Rational& rhd)
{
	return Rational(lhd.numerator * rhd.denominator - rhd.numerator * lhd.denominator, lhd.denominator*rhd.denominator);
}
Rational operator*(const Rational& lhd, const Rational& rhd)
{
	return Rational(lhd.numerator * rhd.numerator, lhd.denominator * rhd.denominator);
}
Rational operator/(const Rational& lhd, const Rational& rhd)
{
	if(rhd.numerator == 0){
		throw domain_error("Division by zero");
	}
	return Rational(lhd.numerator * rhd.denominator, lhd.denominator * rhd.numerator);
}
istream& operator>>(istream& stream, Rational& R)
{
	stream >> R.numerator;
	stream.ignore(1);
	stream >> R.denominator;
	R.Update(R.numerator, R.denominator);
	return stream;
}
ostream& operator<<(ostream& stream, const Rational& R)
{
	stream << R.numerator << "/" << R.denominator;
	return stream;
}
bool operator<(const Rational& lhd, const Rational& rhd)
{
	if(lhd.numerator*rhd.denominator < rhd.numerator*lhd.denominator){
		return true;
	}
	else{
		return false;
	}
}
bool operator>(const Rational& lhd, const Rational& rhd)
{
	if(lhd.numerator*rhd.denominator > rhd.numerator*lhd.denominator){
		return true;
	}
	else{
		return false;
	}
}

void TestConstractorWithDefault(){
	Rational p;
	AssertEqual(p.Denominator(), 1, "CheckDenominator");
	AssertEqual(p.Numerator(), 0, "CheckNumerator");
}

void TestReduceConstractor(){
	Rational p(5, 10);
	AssertEqual(p.Denominator(), 2, "CheckDenominator");
	AssertEqual(p.Numerator(), 1, "CheckNumerator");
	Rational n(121, 363);
	AssertEqual(n.Denominator(), 3, "CheckDenominator");
	AssertEqual(n.Numerator(), 1, "CheckNumerator");
}

void TestNegative(){
	Rational p(-1, 2);
	Rational n(1, -2);
	AssertEqual(p.Denominator(), 2, "CheckDenominator");
	AssertEqual(p.Numerator(), -1, "CheckNumerator");
	AssertEqual(n.Denominator(), 2, "CheckDenominator");
	AssertEqual(n.Numerator(), -1, "CheckNumerator");
}

void TestPositive(){
	Rational p(-5, -7);
	Rational n(5,7);
	AssertEqual(p.Denominator(), 7, "CheckDenominator");
	AssertEqual(p.Numerator(), 5, "CheckNumerator");
	AssertEqual(n.Denominator(), 7, "CheckDenominator");
	AssertEqual(n.Numerator(), 5, "CheckNumerator");
}

void TestZeroNumerator(){
	Rational p(0, 256);
	Rational n(0, 1256);
	AssertEqual(p.Denominator(), 1, "CheckDenominator");
	AssertEqual(p.Numerator(), 0, "CheckNumerator");
	AssertEqual(n.Denominator(), 1, "CheckDenominator");
	AssertEqual(n.Numerator(), 0, "CheckNumerator");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestConstractorWithDefault, "TestConstractorWithDefault");
  runner.RunTest(TestReduceConstractor, "TestReduceConstractor");
  runner.RunTest(TestNegative, "TestNegative");
  runner.RunTest(TestPositive, "TestPositive");
  runner.RunTest(TestZeroNumerator, "TestZeroNumerator");
  return 0;
}
