
#include "Zombie.hpp"
/*
    Allocation dynamique (heap)

    Zombie* newZombie(std::string name) :
    - On crée un Zombie avec "new"
    - Il vit sur la heap, donc il survit à la fin de la fonction.
    - On renvoie un pointeur vers lui.

    - Toute allocation avec new doit être libérée avec delete.
*/
Zombie*	newZombie(std::string name) {
	return new Zombie(name);
}
