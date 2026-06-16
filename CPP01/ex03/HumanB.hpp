
#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"
/*
  Classe HumanB

  - HumanB peut NE PAS avoir d'arme.
  - Il ne reçoit pas l'arme dans son constructeur.

  Donc ici on utilise un pointeur (Weapon*):
  - Un pointeur peut être NULL (0) -> "pas d'arme".
  - Plus tard, on peut donner une arme avec setWeapon().
*/
class HumanB {
	private:
		std::string _name;
		Weapon*		_weapon;

	public:
		HumanB(std::string name);
		~HumanB();
		
		void	attack() const;
		void	setWeapon(Weapon& weapon);

};

#endif
