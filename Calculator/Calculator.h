#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "Operations.h"
#include <sstream>
#include "Loader.h"



class Calculator
{
	std::string parser(std::string exp);
	std::stack<double> numbers;
	Loader loader;
public:
	Calculator() = default;
	~Calculator() = default;
	double calculate(std::string exp);
};

