#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
private:
    Brain* _brain; // Attribut privé

public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    virtual ~Dog();

    void makeSound() const;
};
