#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "Operations.h"
#include<Windows.h>


using unary = double(*)(double);
using binary = double(*)(double, double);

class Loader {
    std::string path = "C:\\Users\\Jeka\\Documents\\GitHub\\Cpp-programming\\Calculator\\plugins\\";
public:
    Loader()=default;
    void loadDll(const std::string& dllFileName);
    void addFunction(const std::string& name);
    double operation(double a, double b, const std::string& name);
    bool binary_contains(const std::string& name);
    bool unary_contains(const std::string& name);
    std::map<std::string, binary> binary_map;
    std::map<std::string, unary> unary_map;
};

