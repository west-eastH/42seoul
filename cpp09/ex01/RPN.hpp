#pragma once

#include <iostream>
#include <stack>
#include <vector>

class RPN
{
	private:
		std::string _exp;
		std::stack<float> _stack;
		RPN();
		RPN(const RPN& origin);
		RPN& operator=(const RPN& origin);
	public:
		RPN(char* exp);
		~RPN();
		void start();
		bool isValidExpression();
		bool checkStack(char op);
		void calculate();
};
