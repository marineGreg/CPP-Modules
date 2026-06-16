
#include "Zombie.hpp"
/*
    Allocation automatique (stack)

    void randomChump(std::string name) :
    - Ici on crée un Zombie "normal" (variable locale).
    - Il vit sur la stack
    - À la fin de la fonction, il est automatiquement détruit (destructeur appelé)

    Avantage:
    - pas de new / delete à gérer -> pas de risque de leaks ici.
*/
void	randomChump(std::string name) {
	Zombie	stackZombie(name);
	stackZombie.announce();
}
