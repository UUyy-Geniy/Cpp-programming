#include "Calculator.h"

std::string takeNum(int& index, const std::string& exp) {
	std::string num = "";
	while ((isdigit(exp[index]) || exp[index] == '.')) {
		num += exp[index];
		index++;
	}
	return num;
}

std::string takeFunc(int& index, const std::string& exp) {
	std::string func = "";
	while (isalpha(exp[index])) {
		func += exp[index];
		index++;
	}
	if (exp[index] != '(') {
		throw std::exception("Func is invalid");
		return "";
	}
	return func;
}

std::vector<std::string> Calculator::parser(const std::string& exp) {
	std::string expression = exp;
	std::string res;
	std::string cur_number;
	std::string current_fun = "";
	std::string::size_type ind;
	std::vector<std::string> result;
	while ((ind = expression.find(' ')) != std::string::npos) expression.erase(ind, 1);

	for (int i = 0; i < expression.size(); ++i) { // (-num) to (0-num)
		if ((expression[i] == '+' || expression[i] == '-') && (i == 0 || (!isdigit(expression[i - 1]) && expression[i - 1] != '.' && expression[i - 1] != ')'))) {
			auto it = std::find_if(expression.begin() + i + 1, expression.end(), [](char const c) {return !isdigit(c); });
			expression.insert(it, ')');
			expression.insert(i, "(0");
		}
	}
	int i = 0;
	char cur_symb;
	std::stack<std::string> stack;
	while (i < expression.size()) {
	
		cur_symb = expression[i];
		if (isdigit(cur_symb)) {
			try {
				cur_number = takeNum(i, expression);
			}
			catch (std::exception& l) {
				throw std::exception(l.what());
				break;
			}
			result.push_back(cur_number);
		}
		else if (isalpha(cur_symb)) {

			try {
				current_fun = takeFunc(i, expression);
			}
			catch (std::exception& e) {
				throw std::exception(e.what());
				break;
			}

			try {
				if (!operations.contains(current_fun)) {
					try {
						loader.loadDll(current_fun,operations);
					}
					catch (std::exception& e) {
						throw std::exception(e.what());
					}
				}
			}
			catch (std::exception& e) {
				throw std::exception(e.what());
				break;
			}

			while (!stack.empty()) {
				if (operations.priority(current_fun) <= operations.priority(stack.top())) {
					result.push_back(stack.top());
					stack.pop();
				}
				else {
					stack.push(current_fun);
					current_fun = "";
					break;
				}
			}

			if (stack.empty()) {
				stack.push(current_fun);
				current_fun = "";
			}


		}
		else if (cur_symb == '(') {
			stack.push({ cur_symb });
			i++;
		}
		else if (cur_symb == ')') {
			while (stack.top() != "(") {

				result.push_back(stack.top());
				stack.pop();
			}
			stack.pop();
			i++;
		}
		else if (operations.contains({ cur_symb })) { // нашли оператор
			while (!stack.empty()) {
				if (operations.priority({ cur_symb }) <= operations.priority(stack.top())) {
					result.push_back(stack.top());
					stack.pop();
				}
				else {
					stack.push({ cur_symb });
					break;
				}
			}
			if (stack.empty()) {
				stack.push({ cur_symb });
			}
			i++;
		}
	}
	while (!stack.empty()) {
		result.push_back(stack.top());
		stack.pop();
	}
	return result;
}


double Calculator::calculate(const std::string& exp) {
	std::vector<std::string> pars = parser(exp);
	std::stack<double> result;
	double arg1 = 0, arg2 = 0;

	for (auto& element : pars) {
		if (isdigit(element[0])) result.push(std::stod(element));
		else {
			arg1 = result.top();
			result.pop();
			if (operations.contains_binary(element)) {
				arg2 = result.top();
				result.pop();
				result.push(operations.calculation(arg1, arg2, element));
			}
			else {
				if (operations.contains_unary({ element })) {
					arg2 = 0;
					result.push(operations.calculation(arg1, arg2, element));
				}
			}
		}
	}
	return result.top();
}