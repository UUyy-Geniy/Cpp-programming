#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include "Loader.h"
#include <vector>

class Calculator
{
	std::vector<std::string> parser(const std::string& exp);	
	std::stack<double> numbers;
	Loader loader;
	Operations operations;
public:
	Calculator() = default;
	~Calculator() = default;
	Calculator(Loader const& loader) : loader(loader), numbers(), operations(Operations::getOperations()) {};
	double calculate(const std::string& exp);
};
 
