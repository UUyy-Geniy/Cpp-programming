#include "Calculator.h"

void isValidSymb(char c) {
	if (c >= -1 && c <= 255) return;
	throw std::exception("Invalid input expression");
}

std::string takeNum(int& index, const std::string& exp) {
	std::string num = "";
	int cnt = 0;
	while ((isdigit(exp[index]) || exp[index] == '.')) {
		if (exp[index] == '.') { cnt++; }
		if (cnt == 2) { throw std::exception("Number is invalid"); }
		num += exp[index];
		index++;
	}
	return num;
} 

std::string takeFunc(int& index, const std::string& exp) {
	std::string func = "";
	while (isalpha(exp[index])||(exp[index])=='^') {
		func += exp[index];
		index++;
	}
	if ((exp[index] != '(') && (exp[index-1]!='^')) {
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
		isValidSymb(expression[i]);
	}
	int i = 0;
	char cur_symb;
	std::stack<std::string> stack;
	while (i < expression.size()) {

		cur_symb = expression[i];
		if (isdigit(cur_symb)) {
			cur_number = takeNum(i, expression);
			result.push_back(cur_number);
		}
		else if (isalpha(cur_symb)||(cur_symb == '^')) {
			current_fun = takeFunc(i, expression);
			if (current_fun == "^") {
				current_fun = "pow";
			}
			if (!operations.contains(current_fun)) {
				loader.loadDll(current_fun, operations);
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
			if (stack.empty()) {
				throw std::exception("Not enough (");
			}
			stack.pop();
			i++;
		}
		else if (operations.contains({ cur_symb })) { 
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
		else { throw std::exception("Symbol is invalid"); }
	}
	while (!stack.empty()) {
		if (stack.top() == "(") {
			throw std::exception("Not enough )");
		}
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
			if (result.empty()) { throw std::exception("Not enough args"); }
			arg1 = result.top();
			result.pop();
			if (operations.contains_binary(element)) {
				if (result.empty()) { throw std::exception("Not enough args"); }
				arg2 = result.top();
				result.pop();
				result.push(operations.calculation(arg2, arg1, element));
			}
			else {
				if (operations.contains_unary( element )) {
					arg2 = 0;
					result.push(operations.calculation(arg1, arg2, element));
				}
			}
		}
	}
	return result.top();
}