#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <sstream>

RPN::RPN() {}

RPN::RPN(const RPN& src) : _stack(src._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        this->_stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::_isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::_performOperation(char op) {
    if (_stack.size() < 2)
    	return false;

    const int right = _stack.top();

	if (op == '/' && right == 0)
		return false; // Division par zero interdite

    _stack.pop();
    
	const int left = _stack.top();
    _stack.pop();

	switch (op) {
		case '+':
			_stack.push(left + right);
			break;
		case '-':
			_stack.push(left - right);
			break;
		case '*':
			_stack.push(left * right);
			break;
		case '/':
			_stack.push(left / right);
			break;
		default:
			return false; // Operateur inconnu
	}
    return true;
}

bool RPN::resolve(const std::string& expression) {
    // Vider la pile si réutilisée
    while (!_stack.empty()) {
    	_stack.pop();
	}

	std::istringstream stream(expression);
	std::string token;

	while (stream >> token)
	{
		if (token.length() != 1)
			return false; // Token invalide (plus d'un caractère)

        char c = token[0];

        if (std::isdigit(static_cast<unsigned char>(c)))
            _stack.push(c - '0');
        else if (_isOperator(c)) {
            if (!_performOperation(c))
                return false;
        } else
            return false; // Caractère invalide (ex: parenthèses, lettres...)
    }

    // Il doit rester exactement un seul résultat dans la pile
    if (_stack.size() != 1)
        return false;

    std::cout << _stack.top() << std::endl;
    return true;
}
