#include "Dog.hpp"

Dog::Dog() {
    std::cout << "Dog constructor" << std::endl;
    this->type = "Dog";
    this->_brain = new Brain(); // Allocation
}

Dog::~Dog() {
    std::cout << "Dog destructor" << std::endl;
    delete this->_brain; // Libération indispensable
}

// CONSTRUCTEUR DE RECOPIE (Deep Copy)
Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor" << std::endl;
    this->_brain = new Brain(*other._brain); // On crée un NOUVEAU cerveau
}

// OPÉRATEUR D'AFFECTATION (Deep Copy)
Dog& Dog::operator=(const Dog& other) {
    std::cout << "Dog assignment operator" << std::endl;
    if (this != &other) {
        this->type = other.type;
        // On supprime l'ancien cerveau pour éviter les fuites
        delete this->_brain; 
        // On en crée un nouveau avec le contenu de l'autre
        this->_brain = new Brain(*other._brain);
    }
    return *this;
}
