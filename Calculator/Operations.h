#pragma once
#include <map>
#include <functional>
#include <string>
#include <iostream>

using unary = double(*)(double);
using binary = double(*)(double, double);

class Operations {
private:
    Operations(); 
    std::map<std::string, binary> operations_binary;
    std::map<std::string, unary> operations_unary;
    std::map<std::string, unsigned short> operations_priority;
public:
    void addBinaryOperation(const std::string& dllFileName, binary& func, unsigned short priority);
    void addUnaryOperation(const std::string& dllFileName, unary& func, unsigned short priority);
    static Operations& getOperations();
    int const priority(const std::string& operationName);
    double calculation(double a, double b, const std::string& name);
    bool contains_binary(const std::string& name);
    bool contains_unary(const std::string& name);
    bool contains(const std::string& name);
};


