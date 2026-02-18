#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int count = 4;
    Animal* animals[count];

    // 1. Remplissage du tableau
    std::cout << "--- CREATING ANIMALS ---" << std::endl;
    for (int i = 0; i < count; i++) {
        if (i < count / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    // 2. Suppression (doit appeler les destructeurs Dog/Cat et Brain !)
    std::cout << "\n--- DELETING ANIMALS ---" << std::endl;
    for (int i = 0; i < count; i++) {
        delete animals[i];
    }

    // 3. Test de la Deep Copy (Copie profonde)
    std::cout << "\n--- DEEP COPY TEST ---" << std::endl;
    Dog basic;
    {
        Dog tmp = basic; // Appel du constructeur de recopie
    } // tmp est détruit ici. Si c'est une shallow copy, basic.brain est détruit aussi -> Crash.
    
    std::cout << "Basic dog is still alive!" << std::endl;

    return 0;
}
