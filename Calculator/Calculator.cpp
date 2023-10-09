#include "Calculator.h"


std::string Calculator::parser(std::string exp) {
	std::string res;

	std::string::size_type ind;
	while ((ind = exp.find(' ')) != std::string::npos) exp.erase(ind, 1); 

	for (int i = 0; i < exp.size(); ++i) { // (-num) to (0-num)
		if ((exp[i] == '+' || exp[i] == '-') && (0 == i || (!isdigit(exp[i - 1]) && exp[i - 1] != '.' && exp[i - 1] != ')'))) {
			auto it = std::find_if(exp.begin() + i + 1, exp.end(), [](char const c) {return !isdigit(c); });
			exp.insert(it, ')');
			exp.insert(i, "(0");
		}
	}

	std::stack<std::string> stack;
	for (auto c : exp) {
		if (!isdigit(c) && ('.' != c)) {
			if (!isalpha(c)) {
				res += ' ';
			}
			else {
				res += c;
				continue;
			}
			if (')' == c) {
				while (stack.top() != "(") {
					res += stack.top();
					stack.pop();
					res += ' ';
				}
				stack.pop();
			}
			else if ('(' == c) {
				stack.push({ c });
			}
			else if (stack.empty() || ((Operations::getOperations().contains({ c }))
				&& (Operations::getOperations().priority(stack.top()) < Operations::getOperations().priority({ c })))) {
				stack.push({ c });
			}
			else {
				do {
					res += stack.top();
					res += ' ';
					stack.pop();
				} while (!(stack.empty() || (Operations::getOperations().priority(stack.top()) < Operations::getOperations().priority({ c }))));
				stack.push({ c });
			}
		}
		else {
			res += c;
		}
	}
	while (!stack.empty()) {
		res += stack.top();
		res += ' ';
		stack.pop();
	}

	return res;
}

double Calculator::calculate(std::string exp) {
	exp = parser(exp);
	std::string curr_num = "";
	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == ' ') {
			if (curr_num == "") {
				continue;
			}
			double num = std::atof(curr_num.c_str());
			numbers.push(num);
			curr_num = "";
			continue;
		}
		if (isdigit(exp[i]) || exp[i] == '.') {
			curr_num.push_back(exp[i]);
		}
		else {
			if (!(curr_num == "")) {
				double num = std::atof(curr_num.c_str());
				numbers.push(num);
				curr_num = "";
			}
			try {
				double a, b;
				if (Operations::getOperations().contains({ exp[i] })) {
					a = numbers.top();
					numbers.pop();
					b = 0;
					b = numbers.top();
					numbers.pop();
					numbers.push(Operations::getOperations().calculation(a, b, { exp[i] }));
				}
				else {
					std::string cur_op = "";
					if (isalpha(exp[i])) {
						while (isalpha(exp[i])) {
							cur_op += exp[i];
							i++;
						}
					}
					if (loader.binary_contains(cur_op) || loader.unary_contains(cur_op)) {
						if (loader.binary_contains(cur_op)) {
							curr_num = "";
							while (isdigit(exp[i]) || exp[i] == ' ' || exp[i] == '.') {
								if (exp[i] == ' ') {
									continue;
								}
								curr_num += exp[i];
								i++;
							}
							double num = std::atof(curr_num.c_str());
							numbers.push(num);
							curr_num = "";
							a = numbers.top();
							numbers.pop();
							b = numbers.top();
							numbers.pop();
							numbers.push(loader.operation(a, b, cur_op));
						}
						else if (loader.unary_contains(cur_op)) {
							curr_num = "";
							i++;
							while (exp[i] != ' ') {
								curr_num += exp[i];
								i++;
							}
							double num = std::atof(curr_num.c_str());
							numbers.push(num);
							curr_num = "";
							a = numbers.top();
							numbers.pop();
							b = 0;
							numbers.push(loader.operation(a, b, cur_op));
						}
					}
					else {
						loader.loadDll(cur_op);
						i = i - cur_op.size() - 1;
					}
				}
			}
			catch (std::exception& e) {
				std::cout << e.what();
			}
		}
	}
	return numbers.top();
}