/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:12:33 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:10:32 by amber            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("Animal") {
    std::cout << "Animal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) {
    std::cout << "Animal copy constructor called" << std::endl;
    *this = other;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
    std::cout << "Animal assignment operator called" << std::endl;
    if (this != &other)
        this->type = other.type;
    return *this;
}

AAnimal::~AAnimal() {
    std::cout << "Animal destructor called" << std::endl;
}

// makeSound() n'est plus défini car c'est une fonction virtuelle pure

std::string AAnimal::getType() const {
    return this->type;
}