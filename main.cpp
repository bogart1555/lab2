#include "pch.h"
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class node {
public:
	T value;
	node *next;
	node(T value) : value(value), next(NULL) {
	}
};

template <typename T>
class Stack {
private:
	node<T> *d;

public:
	Stack() {
		this->d = NULL;
	}

	void push(T value) {
		node<T> *n = new node<T>(value);
		n->next = d;
		d = n;
	}

	T pop() {
		if (d == NULL) {
			throw logic_error("stack is empty");
		}
		T ret = d->value;
		node<T> *t = d;
		d = d->next;
		delete t;
		return ret;
	}

	bool empty() {
		return d == NULL;
	}

	T top() {
		if (d == NULL) {
			throw logic_error("stack is empty");
		}
		return d->value;
	}
};

class ExpressionEvaluator {
private:
	static int precedence(char op) {
		if (op == '+' || op == '-') {
			return 1;
		}
		if (op == '*' || op == '/') {
			return 2;
		}
		return 0;
	}

	static int apply(int b, int a, char op) {
		switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			return a / b;
		}
		throw logic_error("invalid op");
	}

public:
	int evaluate(string str) {
		Stack<int> values;
		Stack<char> ops;

		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ' ') {
				continue;
			}
			else if (str[i] == '(') {
				ops.push(str[i]);
			}
			else if (isdigit(str[i])) {
				int val = 0;

				while (i < str.length() && isdigit(str[i])) {
					val = (val * 10) + (str[i] - '0');
					i++;
				}
				i--;

				values.push(val);
			}
			else if (str[i] == ')') {
				while (!ops.empty() && ops.top() != '(') {
					values.push(apply(values.pop(), values.pop(), ops.pop()));
				}
				ops.pop();
			}
			else {
				while (!ops.empty() && precedence(ops.top()) >= precedence(str[i])) {
					values.push(apply(values.pop(), values.pop(), ops.pop()));
				}
				ops.push(str[i]);
			}
		}

		while (!ops.empty()) {
			values.push(apply(values.pop(), values.pop(), ops.pop()));
		}

		return values.top();
	}
};

int main(int argc, char **argv) {
	cout << "hello world" << endl;


	
	argc = 6;
	argv = new char *[argc];
	argv[1] = (char *) "1";
	argv[2] = (char *) "+";
	argv[3] = (char *) "2";
	argv[4] = (char *) "*";
	argv[5] = (char *) "4+1";



	string str = "";
	for (int i = 1; i < argc; i++) {
		str += argv[i];
	}

	ExpressionEvaluator ev;
	int result = ev.evaluate(str);

	cout << "result: " << result << endl;

	return 0;
}
