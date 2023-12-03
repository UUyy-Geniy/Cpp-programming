#pragma once
#include "Wrapper.h"

class Engine {
public:
	bool register_command(Wrapper* wrapper, const std::string& command_name) {
		if (wrappers.find(command_name) != wrappers.end()) {
			std::cout << "ERROR: This command is already registered." << std::endl;
			return false;
		}
		wrappers[command_name] = wrapper;
	}
	int execute(const std::string& command_name, const ArgsMap& args_map) {
		if (wrappers.find(command_name) != wrappers.end()) {
			return wrappers[command_name]->execute(args_map);
		}
		else {
			throw std::exception("ERROR: Command was not registered.");
		}
	}
private:
	std::map<std::string, Wrapper*> wrappers;
};