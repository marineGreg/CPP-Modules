#include <iostream>
#include <cstdlib> // Pour rand()
#include <ctime>   // Pour time()
#include "Span.hpp"

int main()
{
    std::cout << "=== TEST DU SUJET ===" << std::endl;
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // Doit afficher 2
    std::cout << "Longest span: " << sp.longestSpan() << std::endl;   // Doit afficher 14

    std::cout << "\n=== TEST AVEC 10 000+ ÉLÉMENTS ET PLAGE D'ITÉRATEURS ===" << std::endl;
    try {
        Span bigSpan(15000);
        std::vector<int> randomNumbers;

        std::srand(std::time(NULL));
        for (int i = 0; i < 15000; ++i) {
            randomNumbers.push_back(std::rand());
        }

        // Ajout de 15 000 nombres d'un coup grâce à la plage d'itérateurs
        bigSpan.addNumber(randomNumbers.begin(), randomNumbers.end());

        std::cout << "Shortest span (bigSpan): " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest span (bigSpan): " << bigSpan.longestSpan() << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
    }

    std::cout << "\n=== TEST D'EXCEPTIONS ===" << std::endl;
    try {
        Span smallSpan(1);
        smallSpan.addNumber(42);
        smallSpan.shortestSpan(); // Doit lever une exception (pas assez d'éléments)
    }
    catch (const std::exception &e) {
        std::cerr << "Exception attrapee: " << e.what() << std::endl;
    }

    return 0;
}
