#pragma once
#include <map>
#include <vector>
#include <functional>

using InputArgs = std::map<std::string, int>;
using ArgsMap = std::map<std::string, int>;

class Wrapper {
public:
	template<typename Subject, typename...	Args>
	Wrapper(Subject* subject, int(Subject::* method)(Args...), const InputArgs& input_args) {
		if (input_args.size() != sizeof...(Args)) {
			throw std::exception("ERROR: The quantity of function parameters does not align with the number of input arguments.");
		}
		for (auto& arg : input_args) {
			argsTitles.push_back(arg.first);
		}
		function = [this, subject, method](const std::vector<int>& argsVector) {
			return func_caller(subject, method, argsVector, std::index_sequence_for<Args...>{});
		};
	}
	int execute(const ArgsMap& args_map) {
		if (args_map.size() != argsTitles.size()) {
			throw std::exception("ERROR: Wrong number of aruments.");
		}
		std::vector<int> argsFunc;
		for (const auto& title : argsTitles) {
			argsFunc.push_back(const_cast<std::map<std::string, int>&>(args_map)[title]);
		}
		return function(argsFunc);
	}
private:
	template <typename Subject, typename Method, std::size_t... I>
	int func_caller(Subject& subject, Method method, const std::vector<int>& args, std::index_sequence<I...>) {
		return (subject->*method)(args[I]...);
	}
	std::function<int(std::vector<int>& argsVector)> function;
	std::vector<std::string> argsTitles;
};