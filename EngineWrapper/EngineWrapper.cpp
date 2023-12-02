#include <iostream>
#include "Subject.h"
#include "Wrapper.h"

int main()
{
	Subject s;
	std::cout << s.f1(1, 3, 4) << std::endl;
	std::cout << s.f2(1, 3, 4) << std::endl;
	std::cout << s.f3(1, 3, 4) << std::endl;

	Subject subj;

	Wrapper wrapper(&subj, &Subject::f2, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });

	std::cout << wrapper.execute({ {"arg1", 0}, {"arg2", 0}, {"arg3", 1} });

	return 0;
}
