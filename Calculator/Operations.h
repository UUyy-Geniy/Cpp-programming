#pragma once
#include <map>
#include <functional>
#include <string>


class Operations {
private:
    Operations();
    std::map<std::string, std::function<double(double, double)>> operations;
    std::map<std::string, unsigned short> operations_priority;
public:
    static Operations& getOperations();
    int const priority(const std::string& operationName);
    double calculation(double a, double b, const std::string& name);
    bool contains(const std::string& name);
};


