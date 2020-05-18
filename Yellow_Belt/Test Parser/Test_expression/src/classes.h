#pragma once

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

struct Node {
  virtual int Evaluate() const = 0;
};

struct Value : public Node {
  Value(char digit);
  int Evaluate() const override;
private:
  const uint8_t _value;
};

struct Variable : public Node {
  Variable(const int &x);
  int Evaluate() const override;
private:
  const int &_x;
};

struct Op : public Node {
  Op(char value);
  const uint8_t precedence;
  int Evaluate() const override;
  void SetLeft(shared_ptr<Node> node);
  void SetRight(shared_ptr<Node> node);
private:
  const char _op;
  shared_ptr<const Node> _left, _right;
};
