
#pragma once
#include <iostream>
#include <string>

class WrongAnimal {

	protected:
    	std::string type;

	public:
    	WrongAnimal();
    	WrongAnimal(const WrongAnimal& other);
    	WrongAnimal& operator=(const WrongAnimal& other);
    	~WrongAnimal(); // PAS de virtual ici

    	void makeSound() const; // PAS de virtual ici
    	std::string getType() const;
};
