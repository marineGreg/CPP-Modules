#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& src) { *this = src; }

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

    int right = _stack.top();
    _stack.pop();
    int left = _stack.top();
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
			if (right == 0)
				return false; // Division par zéro interdite
			_stack.push(left / right);
			break;
		default:
			return false; // Opérateur inconnu
	}
    return true;
}

bool RPN::resolve(const std::string& expression) {
    // Vider la pile si réutilisée
    while (!_stack.empty())
        _stack.pop();

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
		
        if (std::isspace(c))
			continue;

        if (std::isdigit(c)) {
            _stack.push(c - '0');
        } else if (_isOperator(c)) {
            if (!_performOperation(c))
                return false;
        } else {
            return false; // Caractère invalide (ex: parenthèses, lettres...)
        }
    }

    // Il doit rester exactement un seul résultat dans la pile
    if (_stack.size() != 1)
        return false;

    std::cout << _stack.top() << std::endl;
    return true;
}
