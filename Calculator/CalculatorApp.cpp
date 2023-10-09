#include "Calculator.h"

int main()
{
	Calculator calculator;
	std::string expression;
	std::cout << "Enter expression(enter ~ to escape):" << std::endl;
	std::getline(std::cin, expression);
	while (expression != "~") {
		try {
			std::cout << expression << "=" << calculator.calculate(expression) << std::endl;
		}
		catch (std::exception& error) {
			std::cout << error.what() << std::endl;
		}
		std::cout << "Enter expression(enter ~ to escape):" << std::endl;
		std::getline(std::cin, expression);
	}

	return 0;
}