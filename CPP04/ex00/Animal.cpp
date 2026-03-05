/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amber <amber@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:12:33 by mgregoir          #+#    #+#             */
/*   Updated: 2026/03/05 18:07:46 by amber            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

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

void AAnimal::makeSound() const {
    std::cout << "Generic Animal sound..." << std::endl;
}

std::string AAnimal::getType() const {
    return this->type;
}