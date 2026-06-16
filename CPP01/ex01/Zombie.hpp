
#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>
/*
  CONCEPTS C++:

    - Class / objet:
      Un Zombie est un objet qui possède un état (son nom) et un comportement (announce()).

    - Encapsulation (private/public):
      Le nom est privé -> on le modifie via une fonction publique setName().

    - Constructeur / Destructeur:
      - Constructeur: appelé à la création de l'objet.
      - Destructeur: appelé à la destruction de l'objet.

    IMPORTANT POUR LA HORDE (zombieHorde):
    - Pour faire "new Zombie[N]", C++ doit pouvoir construire N objets:
      -> il faut un constructeur par défaut Zombie().
*/
class Zombie {
	private:
		std::string _name;

	public:
		Zombie();
		Zombie(const std::string name);
		~Zombie();
		
		void	announce(void);
		void	setName(std::string name);

};

Zombie* zombieHorde(int N, std::string name);

#endif
