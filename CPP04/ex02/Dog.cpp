
#include "Dog.hpp"

Dog::Dog() {
    std::cout << "Dog constructor called" << std::endl;
    this->type = "Dog";
    this->_brain = new Brain();
}

// CONSTRUCTEUR DE COPIE (Deep Copy)
Dog::Dog(const Dog& other) : AAnimal(other) {
	std::cout << "Dog copy constructor called" << std::endl;
    this->_brain = new Brain(*other._brain);
}

// OPERATEUR D'ASSIGNATION (Deep Copy)
Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
		this->type = other.type;
        delete this->_brain; 
        this->_brain = new Brain(*other._brain);
    }
    return *this;
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
	delete this->_brain;
}

void Dog::makeSound() const { std::cout << "Woooof !" << std::endl; }
