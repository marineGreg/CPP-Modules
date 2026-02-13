/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:25 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/13 12:22:58 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// Constructeur par défaut : initialise la valeur à 0
Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

// Constructeur de recopie : appelle l'opérateur d'affectation pour copier la donnée
Fixed::Fixed(const Fixed &src) {
    std::cout << "Copy constructor called" << std::endl;
    // On aurait pu faire _value = src.getRawBits(), 
    // mais passer par l'opérateur d'affectation est une pratique courante.
    *this = src;
}

// Opérateur d'affectation : vérifie l'auto-affectation et copie la valeur
Fixed &Fixed::operator=(const Fixed &rhs) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_value = rhs.getRawBits();
    return *this;
}

// Destructeur
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

// Getter
int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->_value;
}

// Setter
void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl;
    this->_value = raw;
}
