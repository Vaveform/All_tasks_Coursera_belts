#pragma once

#include "classes.h"

template <class Iterator>
shared_ptr<Node> Parse(Iterator token, Iterator end, const int &x) {
  // Empty expression
  if (token == end) {
    return make_shared<Value>('0');
  }

  stack<shared_ptr<Node>> values;
  stack<shared_ptr<Op>> ops;

  auto PopOps = [&](int precedence) {
    while (!ops.empty() && ops.top()->precedence >= precedence) {
      auto value1 = values.top();
      values.pop();
      auto value2 = values.top();
      values.pop();
      auto op = ops.top();
      ops.pop();

      op->SetRight(value1);
      op->SetLeft(value2);

      values.push(op);
    }
  };

  while (token != end) {
    const auto &value = *token;
    if (value >= '0' && value <= '9') {
      values.push(make_shared<Value>(value));
    } else if (value == 'x') {
      values.push(make_shared<Variable>(x));
    } else if (value == '*') {
      PopOps(2);
      ops.push(make_shared<Op>(value));
    } else if (value == '+' || value == '-') {
      PopOps(1);
      ops.push(make_shared<Op>(value));
    }

    ++token;
  }

  while (!ops.empty()) {
    PopOps(0);
  }

  return values.top();
}
