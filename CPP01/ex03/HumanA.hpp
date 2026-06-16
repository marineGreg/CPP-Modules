
#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"
/*
  Classe HumanA

  Différence importante (par rapport à HumanB):
  - HumanA est TOUJOURS armé.
  - On reçoit l'arme au constructeur.
  - Donc on peut stocker l'arme comme une référence (Weapon&).

  CONCEPT C++: référence (Weapon&)
  - Une référence doit toujours référencer un objet valide.
  - On ne peut pas la laisser vide (pas comme un pointeur NULL).
*/
class HumanA {
	private:
		std::string	_name;
		Weapon&		_weapon;

	public:
		HumanA(std::string name, Weapon& weapon);
		~HumanA();
		
		void	attack() const;
};

#endif
