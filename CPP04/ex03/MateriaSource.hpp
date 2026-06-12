
#pragma once

#include "IMateriaSource.hpp"

/**
 * CONCEPT : PATTERN SOURCE / TEMPLATE
 * - Stocke des exemplaires "modèles" de Materias.
 * - createMateria() utilise le polymorphisme (clone()) pour générer de nouveaux
 *   objets sans connaître leur type exact (Ice ou Cure).
 */
class MateriaSource : public IMateriaSource {

	private:
		AMateria* _templates[4]; // Maximum 4 templates

	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator=(const MateriaSource& other);
		~MateriaSource();

		void learnMateria(AMateria* m);
		AMateria* createMateria(std::string const & type);
};

