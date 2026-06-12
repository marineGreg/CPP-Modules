
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

int main()
{
	std::cout << "=== TEST 1: Main du sujet ===" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		ICharacter* me = new Character("me");
		
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		
		ICharacter* bob = new Character("bob");
		
		me->use(0, *bob);
		me->use(1, *bob);
		
		delete bob;
		delete me;
		delete src;
	}

	std::cout << "\n=== TEST 2: Test de copie profonde (Deep Copy) ===" << std::endl;
	{
		Character* original = new Character("Hero");
		
		AMateria* ice = new Ice();
		AMateria* cure = new Cure();
		original->equip(ice);
		original->equip(cure);
		
		Character* copy = new Character(*original); // Constructeur de copie
		
		std::cout << "Original name: " << original->getName() << std::endl;
		std::cout << "Copy name: " << copy->getName() << std::endl;
		
		// Test que les inventaires sont indépendants
		Character dummy("Dummy");
		original->use(0, dummy);
		copy->use(0, dummy);
		
		delete original;
		delete copy;
	}

	std::cout << "\n=== TEST 3: Inventaire plein ===" << std::endl;
	{
		Character* hero = new Character("Hero");
		
		hero->equip(new Ice());
		hero->equip(new Cure());
		hero->equip(new Ice());
		hero->equip(new Cure());
		hero->equip(new Ice()); // Inventaire plein, devrait être droppé
		
		delete hero;
	}

	std::cout << "\n=== TEST 4: Unequip et réutilisation ===" << std::endl;
	{
		Character* hero = new Character("Hero");
		Character* target = new Character("Target");
		
		hero->equip(new Ice());
		hero->equip(new Cure());
		
		hero->use(0, *target); // Utilise Ice
		hero->unequip(0);      // Retire Ice (mais ne le delete pas)
		hero->use(0, *target); // Slot 0 est vide, pas d'effet
		hero->use(1, *target); // Utilise Cure (toujours là)
		
		delete hero;  // Ici, les materias unequip sont supprimées du floor
		delete target;
	}

	std::cout << "\n=== TEST 5: MateriaSource inconnu ===" << std::endl;
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		
		AMateria* tmp = src->createMateria("cure"); // N'a pas été appris
		if (tmp == NULL)
			std::cout << "Cannot create unknown materia type 'cure'" << std::endl;
		
		tmp = src->createMateria("ice"); // OK
		if (tmp)
			std::cout << "Created materia: " << tmp->getType() << std::endl;
		
		delete tmp;
		delete src;
	}

	std::cout << "\n=== TEST 6: Clone de Materia ===" << std::endl;
	{
		AMateria* original = new Ice();
		AMateria* cloned = original->clone();
		
		std::cout << "Original type: " << original->getType() << std::endl;
		std::cout << "Cloned type: " << cloned->getType() << std::endl;
		
		Character target("Target");
		original->use(target);
		cloned->use(target);
		
		delete original;
		delete cloned;
	}

	return 0;
}
