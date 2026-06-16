
#include "Dog.hpp"

Dog::Dog() {
    std::cout << "Dog constructor called" << std::endl;
    this->type = "Dog";
    this->_brain = new Brain(); // Allocation
}

// CONSTRUCTEUR DE COPIE (Deep Copy)
Dog::Dog(const Dog& other) : Animal(other) {
	std::cout << "Dog copy constructor called" << std::endl;
    this->_brain = new Brain(*other._brain);   // On cree un NOUVEAU cerveau
}

// OPERATEUR D'ASSIGNATION (Deep Copy)
Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog assignment operator called" << std::endl;
    if (this != &other) {
		this->type = other.type;
        delete this->_brain;      // On supprime l'ancien cerveau pour eviter les fuites
        this->_brain = new Brain(*other._brain);    // On en cree un nouveau avec le contenu de l'autre
    }
    return *this;
}

Dog::~Dog() {
	delete this->_brain; // Liberation indispensable
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound() const { std::cout << "Woooof !" << std::endl; }
