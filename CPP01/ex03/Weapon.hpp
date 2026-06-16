
#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>
# include <iostream>
/*
  Classe Weapon

  CONCEPTS C++:
  - Attribut privé: on protège les données de la classe (encapsulation).
  - getType() renvoie une "référence constante" (const std::string&):
    -> on évite de copier la string
    -> le "const" empêche de modifier le type via la référence retournée
*/
class Weapon {
	private:
		std::string _type;

	public:
		Weapon(std::string type);
		~Weapon();
		
		const std::string& getType() const;
		void	setType(const std::string& newType);

};

#endif
