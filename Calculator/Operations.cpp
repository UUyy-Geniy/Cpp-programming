#include "Operations.h"


Operations::Operations() {
	operations["+"] = [](double a, double b)->double {return b + a; };
	operations["-"] = [](double a, double b)->double {return b - a; };
	operations["*"] = [](double a, double b)->double {return b * a; };
	operations["/"] = [](double a, double b)->double {return b / a; };

	operations_priority.insert(std::make_pair("*", 3));
	operations_priority.insert(std::make_pair("/", 3));
	operations_priority.insert(std::make_pair("+", 2));
	operations_priority.insert(std::make_pair("-", 2));
	operations_priority.insert(std::make_pair("(", 1));
};

Operations& Operations::getOperations() {
	static Operations instance;
	return instance;
};

int const Operations::priority(const std::string& operation) {
	return operations_priority[operation];
}

double Operations::calculation(double a, double b, const std::string& name) {
	return operations[name](a, b);
};

bool Operations::contains(const std::string& name) {
	return operations.find(name) != operations.end();
}