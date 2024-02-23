#include "RPN.hpp"

RPN::RPN(char* exp) : _exp(exp) {}

RPN::~RPN(){}

bool RPN::isValidExpression()
{                       
	std::string oper = "+-/*";
	bool flag = false;
	for (size_t i = 0; i < _exp.length(); i++)
	{
		if (_exp[i] == ' ')
		{
			if (flag == false || i == _exp.length() - 1)
				return false;
			flag = false;
			continue ;
		}
		if (_exp[i] < '0' || _exp[i] > '9')
		{
			if (oper.find(_exp[i]) == std::string::npos)
				return false;
		}
		if (flag == true)
			return false;
		flag = true;
		_vec.push_back(_exp[i]);
	}
	return true;
}

bool RPN::checkStack(char op)
{
	if (_stack.size() < 2)
	{
		std::cout << "Error" << std::endl;
		return true;
	}
	int b = _stack.top();
	_stack.pop();
	int a = _stack.top();
	_stack.pop();
	switch (op)
	{
		case '+' :
			_stack.push(a + b);
			break ;
		case '-' :
			_stack.push(a - b);
			break ;
		case '/' :
			if (b == 0)
			{
				std::cout << "Not divisible by zero" << std::endl;
				return true;
			}
			_stack.push(a / b);
			break ;
		case '*' :
			_stack.push(a * b);
			break ;
		default:
			std::cout << "Error" << std::endl;
			return true;
	}
	return false;
}

void RPN::calculate()
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] >= '0' && _vec[i] <= '9')
		{
			_stack.push(_vec[i] - '0');
			continue;
		}
		if (checkStack(_vec[i]))
			return ;
	}
	if (_stack.size() != 1)
	{
		std::cout << "Error" << std::endl;
		return ;
	}
	std::cout << _stack.top() << std::endl;
}

void RPN::start()
{
	if (!isValidExpression())
	{
		std::cout << "Error" << std::endl;
		return ;
	}
	calculate();
}