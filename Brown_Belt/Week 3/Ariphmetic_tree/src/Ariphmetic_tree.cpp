#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class Number final: public Expression {
public:
	explicit Number(int init_value) : value(init_value){};
	virtual int Evaluate() const override{
		return value;
	}
	virtual std::string ToString() const override{
		return std::to_string(value);
	}
private:
	int value;
};

class BinaryOperation : public Expression{
public:
	virtual int Evaluate() const override{
		return 0;
	};
	virtual std::string ToString() const override{
		return "";
	};
protected:
	ExpressionPtr left_;
	ExpressionPtr right_;
};

class SumValues final : public BinaryOperation{
public:
	SumValues(ExpressionPtr left, ExpressionPtr right){
		this->left_ = std::move(left);
		this->right_ = std::move(right);
	};
	virtual int Evaluate() const override{
		return left_->Evaluate() + right_->Evaluate();
	}
	virtual std::string ToString() const override{
	    std::string calculated = "(" + left_->ToString() + ")" + "+" + "(" + right_->ToString() + ")";
		return calculated;
	}
};

class MultiplyValues final : public BinaryOperation{
public:
	MultiplyValues(ExpressionPtr left, ExpressionPtr right){
		this->left_ = std::move(left);
		this->right_ = std::move(right);
	}
	virtual int Evaluate() const override{
		return left_->Evaluate() * right_->Evaluate();
	}
	virtual std::string ToString() const override{
		std::string calculated = "(" + left_->ToString() + ")" + "*" + "(" + right_->ToString() + ")";
		return calculated;
	}
};

ExpressionPtr Value(int value){
	return std::make_unique<Number>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
	return std::make_unique<SumValues>(move(left), move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
	return std::make_unique<MultiplyValues>(move(left), move(right));
}

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  auto op = make_unique<BinaryOperation>();
  return 0;
}
