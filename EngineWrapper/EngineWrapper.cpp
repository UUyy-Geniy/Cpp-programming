#include <iostream>
#include "Subject.h"

int main()
{
	Subject s;
	std::cout << s.f1(1, 3, 4) << std::endl;
	std::cout << s.f2(1, 3, 4) << std::endl;
	std::cout << s.f3(1, 3, 4) << std::endl;
	return 0;
}
