
#include "Zombie.hpp"
/*
  zombieHorde()

  CONCEPTS C++:
  - new[] : alloue un tableau d'objets sur la heap (une seule allocation)
  - delete[] : libère le tableau alloué avec new[]
  - initialisation : après new Zombie[N], on donne un nom à chaque Zombie
*/
Zombie* zombieHorde(int N, std::string name) {
	Zombie* horde = new Zombie[N];
	
	for (int i = 0; i < N; i++) {
		horde[i].setName(name);
	}
	return horde;
}
