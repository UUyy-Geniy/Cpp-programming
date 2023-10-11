#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "Operations.h"
#include<Windows.h>

class Loader {
    std::string path = "C:\\Users\\Jeka\\Documents\\GitHub\\Cpp-programming\\Calculator\\plugins\\";
public:
    void loadDll(const std::string& dllFileName, Operations& operations);
};

