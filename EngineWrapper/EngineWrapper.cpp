#include <iostream>
#include "Subject.h"
#include "Engine.h"

int main()
{
	Subject subject;
	Wrapper wrapper1(&subject, &Subject::f1, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });
	Wrapper wrapper2(&subject, &Subject::f2, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });
	Wrapper wrapper3(&subject, &Subject::f3, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });
	Engine engine;
	engine.register_command(&wrapper1, "command1");
	engine.register_command(&wrapper2, "command2");
	engine.register_command(&wrapper3, "command3");
	std::cout << "arg1 * arg2 * arg3 = " << engine.execute("command1", {{"arg1", 2}, {"arg2", 5}, {"arg3", 1}}) << std::endl;
	std::cout << "arg1 + arg2 + arg3 = " << engine.execute("command2", { {"arg1", 2}, {"arg2", 5}, {"arg3", 1} }) << std::endl;
	std::cout << "(arg1 + arg2 + arg3) * 2 = " << engine.execute("command3", { {"arg1", 2}, {"arg2", 5}, {"arg3", 1} }) << std::endl;
	return 0;
}
