#pragma once
#include <string>


class Calculator
{
	Calculator() = default;
	~Calculator() = default;
	std::string parser(std::string exp);
public:
	Calculator(const Calculator&) = delete;
	Calculator& operator=(Calculator const&) = delete;
	Calculator(Calculator&&) = delete;
	Calculator& operator=(Calculator&&) = delete;

	static Calculator& getInstance();
	double calculate(std::string exp);
};

