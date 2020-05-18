#include "classes.h"

Value::Value(char digit) : _value(digit - '0') {}
int Value::Evaluate() const{
	return _value;
}

Variable::Variable(const int &x) : _x(x) {}
int Variable::Evaluate() const{
	return _x;
}

Op::Op(char value): precedence([value] {
    if (value == '*') {
      return 2;
    } else {
      return 1;
    }
  }()),
  _op(value) {}
int Op::Evaluate() const
{
	if (_op == '*') {
	  return _left->Evaluate() * _right->Evaluate();
	} else if (_op == '+') {
	  return _left->Evaluate() + _right->Evaluate();
	} else if (_op == '-') {
	  return _left->Evaluate() - _right->Evaluate();
	}
	return 0;
}
void Op::SetLeft(shared_ptr<Node> node){
	_left = node;
}
void Op::SetRight(shared_ptr<Node> node){
	_right = node;
}
