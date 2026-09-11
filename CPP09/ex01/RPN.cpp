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

/** 
 * Vérifie si un caractère correspond à un opérateur autorisé : +, -, *, /.
 */
bool RPN::_isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/**
 * Applique un operateur aux deux valeurs placees au sommet de la pile.
 * La valeur de droite est retiree en premier, puis la valeur de gauche.
 * Le resultat est ensuite remis sur la pile.
 */
bool RPN::_performOperation(char op) {
    if (_stack.size() < 2)
    	return false;

    const int right = _stack.top(); // Valeur de droite est extraite en premier

	if (op == '/' && right == 0)
		return false; // Division par zero interdite

    _stack.pop();
    
	const int left = _stack.top(); // Valeur de gauche est extraite en second
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

/**
 * Analyse et evalue une expression en RPN complete.
 */
bool RPN::resolve(const std::string& expression) {
    // Vider la pile avant de commencer l'evaluation
    while (!_stack.empty()) {
    	_stack.pop();
	}
	// istringstream découpe l'expression en tokens séparés par espaces, tab ou blancs.
	std::istringstream stream(expression);
	std::string token;

	// Parcourir chaque token de l'expression
	while (stream >> token) // operator>> surcharge de classe istringstream pour extraire la data formatee
	{
		if (token.length() != 1)
			return false; // Token invalide (plus d'un caractère)

        char c = token[0];

		if (std::isdigit(static_cast<unsigned char>(c))) // Si le token est un chiffre
            _stack.push(c - '0'); // Convertir le caractere en entier et l'empiler
        else if (_isOperator(c)) { // Si le token est un operateur
            if (!_performOperation(c)) // Effectuer l'operation
                return false;
        } else
            return false; // Caractere invalide
    }

    // Il doit rester exactement un seul résultat dans la pile
    if (_stack.size() != 1)
        return false;

    std::cout << _stack.top() << std::endl;
    return true;
}
