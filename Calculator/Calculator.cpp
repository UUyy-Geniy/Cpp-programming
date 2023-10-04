#include "Calculator.h"

Calculator& Calculator::getInstance() {
    static Calculator instance;
    return instance;
};

std::string Calculator::parser(std::string exp) {
    return "";
}

double Calculator::calculate(std::string exp) {
    return 0;
}
