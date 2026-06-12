
#pragma once
#include <iostream>
#include <string>

class ICharacter; // Forward declaration

/**
 * CONCEPT : CLASSE ABSTRAITE AVEC DONNÉES
 * - Abstraction : Contient un attribut 'type' commun à toutes les Materias.
 * - Pattern Prototype : Définit la méthode virtuelle pure clone() qui sera 
 *   implémentée par Ice et Cure pour s'auto-dupliquer.
 */
class AMateria {

	protected:
		std::string _type;

	public:
		AMateria();
		AMateria(std::string const & type);
		AMateria(const AMateria& other);
		AMateria& operator=(const AMateria& other);
		virtual ~AMateria();

		std::string const & getType() const; // Returns the materia type
		
		virtual AMateria* clone() const = 0; // Pure virtual -> Interface
		virtual void use(ICharacter& target); // Behavior peut être overridé
};

