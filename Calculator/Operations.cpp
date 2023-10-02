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

Operations& Operations::getInstance() {
    static Operations instance;
    return instance;
};

int const Operations::priority(std::string const& operationName) {
    return operations_priority[operationName];
}

double Operations::operation(double const& a, double const& b, std::string const& name) {
    return operations[name](a, b);
}

bool Operations::contains(std::string const& name) {
    return operations.find(name) != operations.end();
}
