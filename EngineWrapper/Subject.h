#pragma once
#include <iostream>

class Subject {
public:
	int f1(int a, int b, int c) { return a * b * c; }
	int f2(int a, int b, int c) { return a + b + c; }
	int f3(int a, int b, int c) { return (a + b + c) * 2; }
};
