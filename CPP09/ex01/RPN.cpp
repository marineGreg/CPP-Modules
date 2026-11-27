#include "RPN.hpp"
#include <cctype>
#include <iostream>
#include <sstream>
#include <climits>

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
 * Analyse et evalue une expression en RPN complete.
 * Chaque token est soit un chiffre unique (0-9), soit un operateur (+, -, *, /).
 * Les tokens sont separes par des espaces.
 * Le resultat final est affiche sur la sortie standard.
 * La fonction retourne true si l'expression est valide et evaluee avec succes.
 */
bool RPN::resolve(const std::string& expression)
{
	while (!_stack.empty()) // Nettoyer la pile avant d'evaluer une nouvelle expression
		_stack.pop();

	// istringstream decoupe l'expression en tokens separes par espaces, tab ou blancs
	std::istringstream stream(expression);
	std::string token;

	// Parcourir chaque token de l'expression
	while (stream >> token)
	{
		if (token.length() != 1)
			return false;

		char c = token[0];
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			_stack.push(c - '0'); // Convertir le caractere en entier et l'empiler
		}
		else if (_isOperator(c))
		{
			if (!_performOperation(c))  
				return false;
		} 
		else
			return false; // Caractere invalide
	}

	// Il doit rester exactement un seul résultat dans la pile
	if (_stack.size() != 1)
		return false;

	std::cout << _stack.top() << std::endl;
	return true;
}

/** 
 * Verifie si un caractere correspond a un operateur autorise : +, -, *, /
 */
bool RPN::_isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/**
 * Applique un opérateur aux deux valeurs au sommet de la pile.
 *
 * La première valeur dépilée est l'opérande droite, la seconde
 * est l'opérande gauche. Cet ordre compte pour la soustraction
 * et la division.
 *
 * Avant le calcul, la méthode vérifie que l'opération ne divise
 * pas par zéro et que son résultat est représentable par un int.
 * Si le calcul réussit, le résultat est empilé.
 */
bool RPN::_performOperation(char op)
{
    if (_stack.size() < 2)
        return false;

    const int right = _stack.top();
    _stack.pop();

    const int left = _stack.top();
    _stack.pop();

    int result;

    switch (op)
    {
        case '+':
            if ((right > 0 && left > INT_MAX - right)
                || (right < 0 && left < INT_MIN - right))
                return false;
            result = left + right;
            break;

        case '-':
            if ((right > 0 && left < INT_MIN + right)
                || (right < 0 && left > INT_MAX + right))
                return false;
            result = left - right;
            break;

        case '*':
            if (left > 0)
            {
                if ((right > 0 && left > INT_MAX / right)
                    || (right < 0 && right < INT_MIN / left))
                    return false;
            }
            else if (left < 0)
            {
                if ((right > 0 && left < INT_MIN / right)
                    || (right < 0 && left < INT_MAX / right))
                    return false;
            }
            result = left * right;
            break;

        case '/':
            if (right == 0 || (left == INT_MIN && right == -1))
                return false;
            result = left / right;
            break;

        default:
            return false;
    }

    _stack.push(result);
    return true;
}
