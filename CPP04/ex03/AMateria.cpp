/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:00:00 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/23 15:00:00 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() : _type("unknown") {
	// std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const & type) : _type(type) {
	// std::cout << "AMateria type constructor called" << std::endl;
}

AMateria::AMateria(const AMateria& other) : _type(other._type) {
	// std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other) {
	// std::cout << "AMateria assignment operator called" << std::endl;
	if (this != &other) {
		// On ne copie PAS le type selon le sujet 42
		// this->_type = other._type;
		(void)other;
	}
	return *this;
}

AMateria::~AMateria() {
	// std::cout << "AMateria destructor called" << std::endl;
}

std::string const & AMateria::getType() const {
	return this->_type;
}

void AMateria::use(ICharacter& target) {
	(void)target; // Pour éviter le warning unused parameter
	std::cout << "* AMateria default use *" << std::endl;
}
