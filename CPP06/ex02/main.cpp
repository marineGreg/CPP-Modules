#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

Base* generate(void) {
	int i = std::rand() % 3;
	if (i == 0)
		return new A;
	if (i == 1)
		return new B;
	return new C;
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void identify(Base& p) {
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return;		
	} catch (std::exception &e) {}

	try {
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return;		
	} catch (std::exception &e) {}
	
	try {
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return;		
	} catch (std::exception &e) {}
}

int main()
{
	std::srand(std::time(NULL));

	std::cout << "===== TEST D'IDENTIFICATION REEL TYPE =====" << std::endl << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "--- Test n°" << i + 1 << " ---" << std::endl;

        // 2. Generation d'un objet aleatoire (A, B ou C)
        Base* instance = generate();

        // 3. Test de l'identification par POINTEUR
        std::cout << "Identification par pointeur  : ";
        identify(instance);

        // 4. Test de l'identification par RÉFÉRENCE
        std::cout << "Identification par reference : ";
        identify(*instance); // On dereference le pointeur pour envoyer la reference

        // 5. Liberation de la memoire
        delete instance;
        std::cout << std::endl;
    }

    return 0;
}
