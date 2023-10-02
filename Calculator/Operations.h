#pragma once
#include <map>
#include <functional>
#include <string>

class Operations {
private:
    Operations();
    std::map<std::string, std::function<double(double, double)>> operations;
    std::map<std::string, size_t> operations_priority;
public:
    Operations(const Operations&) = delete;
    Operations& operator=(Operations const&) = delete;
    Operations(Operations&&) = delete;
    Operations& operator=(Operations&&) = delete;

    static Operations& getInstance();
    int const priority(std::string const& operationName);
    double operation(double const& a, double const& b, std::string const& name);
    bool contains(std::string const& name);
};


