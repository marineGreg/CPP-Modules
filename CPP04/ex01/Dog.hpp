
#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	
	private:
    	Brain* _brain; // Attribut prive
	
	public:
    	Dog();
    	Dog(const Dog& other);
    	Dog& operator=(const Dog& other);
    	~Dog();

    	void makeSound() const;
};

