#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const
{
	return true;
}
DateComparisonNode::DateComparisonNode(const enum Comparison cmp,
		const Date d) : _type(cmp), _date(d) {}
bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
	if(this->_type == Comparison::Equal){
		return date == this->_date;
	}
	else if(this->_type == Comparison::Greater){
		return date > this->_date;
	}
	else if(this->_type == Comparison::GreaterOrEqual){
		return date >= this->_date;
	}
	else if(this->_type == Comparison::Less){
		return date < this->_date;
	}
	else if(this->_type == Comparison::LessOrEqual){
		return date <= this->_date;
	}
	else if(this->_type == Comparison::NotEqual)
	{
		return date != this->_date;
	}
}

EventComparisonNode::EventComparisonNode(const enum Comparison cmp,
		const string e) : _type(cmp), _event(e) {}
bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	if(this->_type == Comparison::Equal){
		return event == this->_event;
	}
	else if(this->_type == Comparison::Greater){
		return event > this->_event;
	}
	else if(this->_type == Comparison::GreaterOrEqual){
		return event >= this->_event;
	}
	else if(this->_type == Comparison::Less){
		return event < this->_event;
	}
	else if(this->_type == Comparison::LessOrEqual){
		return event <= this->_event;
	}
	else if(this->_type == Comparison::NotEqual)
	{
		return event != this->_event;
	}
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
