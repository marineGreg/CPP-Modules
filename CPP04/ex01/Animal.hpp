
#pragma once

#include <iostream>
#include <string>

class Animal {

	protected:
    	std::string type;

	public:
    	Animal();
    	Animal(const Animal& other);
    	Animal& operator=(const Animal& other);
    	virtual ~Animal(); // Virtuel pour permettre la destruction des classes dérivées

    	virtual void makeSound() const;
    	std::string getType() const;
};
