
#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include "Contact.hpp"

/*
  CONCEPTS C++ :

    - Agrégation d'objets:
      La classe PhoneBook contient un tableau de 8 objets 'Contact'.
      C'est une classe qui gère d'autres classes.

    - Gestion de la mémoire (Stack vs Heap):
      Le sujet interdit l'allocation dynamique ('new' est interdit).
      Le tableau de contacts est donc alloué de manière statique 
      (sur la pile/stack) dès la création du PhoneBook.

    - Flux d'entrée/sortie (std::iostream & std::iomanip):
      - std::getline(): Pour lire une ligne entière (gère les espaces).
      - std::setw(10): Pour définir une largeur de colonne fixe.
      - std::right: Pour aligner le texte à droite (comportement par défaut).

    - Logique circulaire (Modulo):
      Utilisation de '_index % 8' pour remplacer automatiquement 
      le contact le plus ancien sans dépasser la taille du tableau.
*/
class PhoneBook {
	private:
		Contact _contacts[8];
		int     _contactCount;
    	int     _index;
		
		void	_printColumn(std::string str) const;
		
	public:
		PhoneBook();
		~PhoneBook();
		
		void addContact();
		void searchContact() const;
};

#endif