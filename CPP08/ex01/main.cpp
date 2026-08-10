#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main()
{
    std::cout << "===== 1. TEST OFFICIEL DU SUJET =====" << std::endl;
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest span (attendu : 2)  -> " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span  (attendu : 14) -> " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== 2. TEST PLAGE D'ITÉRATEURS (15 000 NOMBRES) =====" << std::endl;
    {
        try {
            unsigned int size = 15000;
            Span bigSpan(size);
            std::vector<int> randomNumbers;

            std::srand(std::time(NULL));
            for (unsigned int i = 0; i < size; ++i) {
                randomNumbers.push_back(std::rand());
            }

            // Remplissage EN UN SEUL APPEL avec la plage d'itérateurs
            bigSpan.addNumber(randomNumbers.begin(), randomNumbers.end());

            std::cout << "Succes de l'ajout en masse de " << size << " elements !" << std::endl;
            std::cout << "Shortest span (15k) : " << bigSpan.shortestSpan() << std::endl;
            std::cout << "Longest span  (15k) : " << bigSpan.longestSpan() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Exception caught : " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 3. PLAGE D'ITÉRATEURS DEPUIS STD::LIST =====" << std::endl;
    {
        try {
            Span sp(5);
            std::list<int> lst;
            lst.push_back(100);
            lst.push_back(200);
            lst.push_back(300);

            // Remplissage depuis une list (prouve la généricité du template)
            sp.addNumber(lst.begin(), lst.end());

            std::cout << "Shortest span depuis list : " << sp.shortestSpan() << std::endl;
            std::cout << "Longest span depuis list  : " << sp.longestSpan() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Exception caught : " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 4. TEST AVEC NOMBRES NÉGATIFS =====" << std::endl;
    {
        Span sp(3);
        sp.addNumber(-20);
        sp.addNumber(0);
        sp.addNumber(20);

        std::cout << "Shortest span (-20, 0, 20) (attendu : 20) -> " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span  (-20, 0, 20) (attendu : 40) -> " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== 5. TESTS D'EXCEPTIONS =====" << std::endl;
    // Test 1: Span plein
    try {
        std::cout << "-> Test ajout au-dela de la limite N... ";
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        sp.addNumber(3);
        std::cout << "[KO] Pas d'exception !" << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "[OK] Exception caught : " << e.what() << std::endl;
    }

    // Test 2: Span vide
    try {
        std::cout << "-> Test shortestSpan sur Span vide... ";
        Span sp(5);
        sp.shortestSpan();
        std::cout << "[KO] Pas d'exception !" << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "[OK] Exception caught : " << e.what() << std::endl;
    }

    // Test 3: Un seul élément
    try {
        std::cout << "-> Test longestSpan avec 1 seul element... ";
        Span sp(5);
        sp.addNumber(42);
        sp.longestSpan();
        std::cout << "[KO] Pas d'exception !" << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "[OK] Exception caught : " << e.what() << std::endl;
    }

    return 0;
}
