
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("Default_clap_name"), FragTrap(), ScavTrap() {
    this->_name = "Default";
    this->_hitPoints = FragTrap::_hitPoints;    // 100
    this->_nrgPoints = ScavTrap::_nrgPoints; // 50
    this->_aDamage = FragTrap::_aDamage; // 30
    std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), FragTrap(), ScavTrap() {
    this->_name = name;
    this->_hitPoints = 100;    // Provient de FragTrap
    this->_nrgPoints = 50;  // Provient de ScavTrap
    this->_aDamage = 30;  // Provient de FragTrap
    std::cout << "DiamondTrap Name constructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other) : ClapTrap(other), FragTrap(other), ScavTrap(other) {
    *this = other;
    std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    if (this != &other) {
        this->_name = other._name;
        this->ClapTrap::_name = other.ClapTrap::_name;
        this->_hitPoints = other._hitPoints;
        this->_nrgPoints = other._nrgPoints;
        this->_aDamage = other._aDamage;
    }
    return *this;
}

DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap Destructor called for " << _name << std::endl;
}

void DiamondTrap::whoAmI() {
    std::cout << "I am DiamondTrap: " << this->_name 
              << " and my ClapTrap name is: " << ClapTrap::_name << std::endl;
}
