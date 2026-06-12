
#pragma once
#include "AMateria.hpp"

/**
 * CONCEPT : INTERFACE DE GÉNÉRATION (FACTORY)
 * - Définit le contrat pour une classe capable d'apprendre des modèles de Materias
 *   et de les cloner sur demande via leur nom.
 */
class IMateriaSource {

	public:
		virtual ~IMateriaSource() {}
		
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};

