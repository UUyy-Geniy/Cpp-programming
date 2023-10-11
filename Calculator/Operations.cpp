#include "Operations.h"

Operations::Operations() {
	operations_binary["+"] = [](double a, double b)->double {return b + a; };
	operations_binary["-"] = [](double a, double b)->double {return a - b; };
	operations_binary["*"] = [](double a, double b)->double {return b * a; };
	operations_binary["/"] = [](double a, double b)->double {if (b != 0) return a / b; throw std::exception("Division by zero!"); };

	operations_priority["*"] = 2;
	operations_priority["/"] = 2;
	operations_priority["+"] = 1;
	operations_priority["-"] = 1;
};

Operations& Operations::getOperations() {
	static Operations instance;
	return instance;
};

void Operations::addBinaryOperation(const std::string& dllFileName, binary& func, unsigned short priority) {
	operations_binary[dllFileName] = func;
	operations_priority[dllFileName] = priority;
}

void Operations::addUnaryOperation(const std::string& dllFileName, unary& func, unsigned short priority) {
	operations_unary[dllFileName] = func;
	operations_priority[dllFileName] = priority;
}

int const Operations::priority(const std::string& operation) {
	return operations_priority[operation];
}

double Operations::calculation(double a, double b, const std::string& name) {
	if (contains_binary(name)) { return operations_binary[name](a, b); }
	if (contains_unary(name)) { return operations_unary[name](a); }
	throw std::exception("Operation was not found");
	return INFINITY;
};

bool Operations::contains_binary(const std::string& name) {
	return operations_binary.find(name) != operations_binary.end();
}

bool Operations::contains_unary(const std::string& name) {
	return operations_unary.find(name) != operations_unary.end();
}

bool Operations::contains(const std::string& name) {
	return contains_unary(name) || contains_binary(name);
}
