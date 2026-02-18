/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:25 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/18 11:34:06 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int n) { this->_value = n << _bits; }

Fixed::Fixed(const float n) { this->_value = roundf(n * (1 << _bits)); }

Fixed::Fixed(const Fixed &other) { *this = other; }

Fixed &Fixed::operator=(const Fixed &other) {
	if (this != &other)
		this->_value = other.getRawBits();
    return *this;
}

Fixed::~Fixed() {}

int Fixed::getRawBits(void) const {
	return this->_value;
}

void Fixed::setRawBits(int const raw) {
	this->_value = raw;
}

float Fixed::toFloat(void) const {
    return (float)this->_value / (1 << _bits); // Division par 256.0
}

int Fixed::toInt(void) const {
    return this->_value >> _bits; // Division entière par 256
}

// --- Comparaisons ---
bool Fixed::operator>(const Fixed &other) const  { return this->_value > other._value; }
bool Fixed::operator<(const Fixed &other) const  { return this->_value < other._value; }
bool Fixed::operator>=(const Fixed &other) const { return this->_value >= other._value; }
bool Fixed::operator<=(const Fixed &other) const { return this->_value <= other._value; }
bool Fixed::operator==(const Fixed &other) const { return this->_value == other._value; }
bool Fixed::operator!=(const Fixed &other) const { return this->_value != other._value; }

// --- Arithmétiques ---
// Pour la précision, on convertit en float, on fait le calcul, et on recrée un Fixed
Fixed Fixed::operator+(const Fixed &other) const { return Fixed(this->toFloat() + other.toFloat()); }
Fixed Fixed::operator-(const Fixed &other) const { return Fixed(this->toFloat() - other.toFloat()); }
Fixed Fixed::operator*(const Fixed &other) const { return Fixed(this->toFloat() * other.toFloat()); }
Fixed Fixed::operator/(const Fixed &other) const { return Fixed(this->toFloat() / other.toFloat()); }

// --- Incrément / Décrément ---
// Pré-incrément : ++a
Fixed &Fixed::operator++(void) {
    this->_value++;
    return *this;
}

// Post-incrément : a++
Fixed Fixed::operator++(int) {
    Fixed tmp(*this); // On fait une copie de l'état actuel
    this->_value++;   // On incrémente l'original
    return tmp;       // On retourne la copie (l'ancienne valeur)
}

Fixed &Fixed::operator--(void) {
    this->_value--;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);
    this->_value--;
    return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Surcharge de << pour afficher le float
std::ostream &operator<<(std::ostream &o, Fixed const &i) {
    o << i.toFloat();
    return o;
}
