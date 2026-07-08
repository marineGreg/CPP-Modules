#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <cstddef>
#include <stdint.h>

/**
 * Il n'y a aucune hiérarchie de classe ni aucun lien de conversion standard
 * entre un pointeur d'objet et un nombre entier. On doit faire une
 * réinterprétation directe des bits au niveau mémoire, ce que seul le 
 * reinterpret_cast permet de faire.
 */
class Serializer
{
	private:
		Serializer();
		Serializer(const Serializer & src);
		Serializer &operator=(const Serializer & other);
		~Serializer();

	public:
		static uintptr_t serialize(Data* ptr);
		static Data * deserialize(uintptr_t raw);
};


#endif
