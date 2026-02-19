/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgregoir <mgregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 16:14:53 by mgregoir          #+#    #+#             */
/*   Updated: 2026/02/19 17:47:23 by mgregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() {
    std::cout << "Cat constructor called" << std::endl;
    this->type = "Cat";
	this->_brain = new Brain();
}

Cat::~Cat() { 
	std::cout << "Cat destructor called" << std::endl;
	delete this->_brain;
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "Cat copy constructor called" << std::endl;
	this->_brain = new Brain(*other._brain);
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "Cat assignment operator called" << std::endl;
    if (this != &other) {
		this->type = other.type;
		delete this->_brain;
		this->_brain = new Brain(*other._brain);
	}
    return *this;
}


void Cat::makeSound() const { std::cout << "Meoowww !" << std::endl; }