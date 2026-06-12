
#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

/**
 * CONCEPT : GESTION D'INVENTAIRE ET DEEP COPY
 * - Implémentation concrète de l'interface ICharacter.
 * - Deep Copy de l'inventaire : Lors d'une copie, on doit delete l'ancien inventaire 
 *   et appeler clone() sur chaque Materia de l'autre personnage.
 * - Gestion du NULL : Initialisation et nettoyage rigoureux des 4 slots d'inventaire.
 */
class Character : public ICharacter {

	private:
		std::string _name;
		AMateria* _inventory[4]; // Maximum 4 Materias
		AMateria* _floor[100];   // Stockage des Materias unequip (pour éviter les leaks)
		int _floorCount;

	public:
		Character();
		Character(std::string const & name);
		Character(const Character& other);
		Character& operator=(const Character& other);
		~Character();

		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};
