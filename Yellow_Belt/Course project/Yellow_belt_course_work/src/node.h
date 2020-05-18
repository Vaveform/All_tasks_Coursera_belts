#pragma once

#include <string>
#include <memory>
#include "date.h"

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	And,
	Or,
};

class Node{
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node{
public:
	DateComparisonNode(const Comparison cmp, const Date d);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _type;
	const Date _date;
};

class EventComparisonNode : public Node{
public:
	EventComparisonNode(const Comparison cmp, const string e);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const Comparison _type;
	const string _event;
};

class LogicalOperationNode: public Node
{
public:
	LogicalOperationNode(const LogicalOperation op,
			shared_ptr<Node> _left, shared_ptr<Node> _right);
	bool Evaluate(const Date& date, const string& event) const override;
private:
	const LogicalOperation _op;
	shared_ptr<const Node> left_, right_;
};
