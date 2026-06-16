
#include "Zombie.hpp"

Zombie::Zombie() : _name("Unnamed") {}

Zombie::Zombie(const std::string name) : _name(name) {
  // Constructeur qui initialise directement le nom.
}

Zombie::~Zombie() {
	std::cout << _name << ": has been destroyed" << std::endl;
}

void Zombie::announce() {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
	// Setter: permet de modifier un attribut privé.
	this->_name = name;
}
