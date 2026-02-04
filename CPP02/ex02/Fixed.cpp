/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:49:25 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/04 16:08:29 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

// --- Constructeurs & Destructeur ---

Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int n) {
    this->_value = n << _bits; // Conversion : n * 256
}

Fixed::Fixed(const float n) {
    this->_value = roundf(n * (1 << _bits)); // Conversion : n * 256 avec arrondi
}

Fixed::Fixed(const Fixed &src) {
    *this = src;
}

Fixed::~Fixed() {
}

// --- Opérateurs ---

Fixed &Fixed::operator=(const Fixed &rhs) {
    if (this != &rhs)
        this->_value = rhs.getRawBits();
    return *this;
}

// --- Conversions ---

float Fixed::toFloat(void) const {
    return (float)this->_value / (1 << _bits); // Division par 256.0
}

int Fixed::toInt(void) const {
    return this->_value >> _bits; // Division entière par 256
}

// --- Get/Set ---

int Fixed::getRawBits(void) const {
    return this->_value;
}

void Fixed::setRawBits(int const raw) {
    this->_value = raw;
}

// --- Comparaisons ---
bool Fixed::operator>(const Fixed &rhs) const  { return this->_value > rhs._value; }
bool Fixed::operator<(const Fixed &rhs) const  { return this->_value < rhs._value; }
bool Fixed::operator>=(const Fixed &rhs) const { return this->_value >= rhs._value; }
bool Fixed::operator<=(const Fixed &rhs) const { return this->_value <= rhs._value; }
bool Fixed::operator==(const Fixed &rhs) const { return this->_value == rhs._value; }
bool Fixed::operator!=(const Fixed &rhs) const { return this->_value != rhs._value; }

// --- Arithmétiques ---
// Pour la précision, on convertit en float, on fait le calcul, et on recrée un Fixed
Fixed Fixed::operator+(const Fixed &rhs) const { return Fixed(this->toFloat() + rhs.toFloat()); }
Fixed Fixed::operator-(const Fixed &rhs) const { return Fixed(this->toFloat() - rhs.toFloat()); }
Fixed Fixed::operator*(const Fixed &rhs) const { return Fixed(this->toFloat() * rhs.toFloat()); }
Fixed Fixed::operator/(const Fixed &rhs) const { return Fixed(this->toFloat() / rhs.toFloat()); }

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
