#include <iostream>
//#include "Calculator.h"
#include <Windows.h>

using namespace std;

int main()
{
    HINSTANCE load;
    load = LoadLibrary(L"./plugins\\Dinamic_cos.dll");
    typedef double (*Sin) (double);
    Sin sinnn;
    sinnn = (Sin)GetProcAddress(load, "func");

    double a = 3.14;
    std::cout << sinnn(a);

    FreeLibrary(load);
    return 0;
}