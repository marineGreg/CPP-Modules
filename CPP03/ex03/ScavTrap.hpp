
#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {

	public:
    	ScavTrap();
    	ScavTrap(std::string name);
    	ScavTrap(const ScavTrap& other);
    	ScavTrap& operator=(const ScavTrap& other);
    	~ScavTrap();

    	// Redéfinition de l'attaque (message différent)
    	void attack(const std::string& target);
    
    	// Capacité spéciale
    	void guardGate();
};

#endif
