
#pragma once

#include <iostream>
#include <string>


/**
 * CONCEPTS C++ :
 * - Polymorphisme de sous-type : Capacité d'utiliser un pointeur de classe de base 
 *   (Animal*) pour manipuler des objets de classes dérivées (Dog, Cat).
 * - Liaison Dynamique (Dynamic Binding) : Utilisation du mot-clé 'virtual' pour 
 *   déterminer la méthode à appeler au moment de l'exécution et non de la compilation.
 * - Destructeur Virtuel : Élément indispensable garantissant la destruction 
 *   complète de l'objet dérivé, évitant ainsi les fuites de mémoire.
 * - Liaison Statique (Static Binding) : Illustration via les classes 'Wrong' du 
 *   comportement par défaut où le type du pointeur prime sur le type de l'objet.
 */
class Animal {

	protected:
    	std::string type;

	public:
    	Animal();
    	Animal(const Animal& other);
    	Animal& operator=(const Animal& other);
    	virtual ~Animal(); // Virtuel pour permettre la destruction des classes derivees

    	virtual void makeSound() const;
    	std::string getType() const;
};
