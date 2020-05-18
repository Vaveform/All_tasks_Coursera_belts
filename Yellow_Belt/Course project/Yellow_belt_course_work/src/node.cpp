#include "node.h"

template <class T>
bool Compare(const T& lhs, const T& rhd, Comparison cmp)
{
	if(cmp == Comparison::Equal){
		return lhs == rhd;
	}
	else if(cmp == Comparison::Greater){
		return lhs > rhd;
	}
	else if(cmp == Comparison::GreaterOrEqual){
		return lhs >= rhd;
	}
	else if(cmp == Comparison::Less){
		return lhs < rhd;
	}
	else if(cmp == Comparison::LessOrEqual){
		return lhs <= rhd;
	}
	else{
		return lhs != rhd;
	}
}

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
	return true;
}
DateComparisonNode::DateComparisonNode(const enum Comparison cmp,
		const Date d) : _type(cmp), _date(d) {}
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	return Compare(date, _date, _type);
}

EventComparisonNode::EventComparisonNode(const enum Comparison cmp,
		const string e) : _type(cmp), _event(e) {}
bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	return Compare(event, _event, _type);
}

LogicalOperationNode::LogicalOperationNode(enum LogicalOperation op,
		shared_ptr<Node> _left, shared_ptr<Node> _right) : _op(op),
				left_(_left), right_(_right){}
bool LogicalOperationNode::Evaluate(const Date & date, const string & event) const{
	if(this->_op == LogicalOperation::And){
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}
	else{
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
	}
}
