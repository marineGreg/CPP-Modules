#include <iostream>
#include <vector>
#include <list>
#include <climits>
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

    std::cout << "\n===== 2. AJOUT PAR PLAGE (15 000 NOMBRES) =====" << std::endl;
    {
        const unsigned int size = 15000;
        Span bigSpan(size);
        std::vector<int> numbers;

		// Pré-allocation de la mémoire pour éviter les reallocations lors de l'ajout
        numbers.reserve(size);
        for (unsigned int i = 0; i < size; ++i)
            numbers.push_back(static_cast<int>(i * 2));

        bigSpan.addNumber(numbers.begin(), numbers.end());

        std::cout << "Shortest span (attendu : 2) -> " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest span (attendu : 29998) -> " << bigSpan.longestSpan() << std::endl;
    }


    std::cout << "\n===== 3. VALEURS EXTREMES : INT_MIN ET INT_MAX =====" << std::endl;
    {
        Span extremes(2);
        int values[] = {INT_MIN, INT_MAX};

        extremes.addNumber(values, values + 2);

        std::cout << "Shortest span (attendu : " << UINT_MAX << ") -> " << extremes.shortestSpan() << std::endl;
        std::cout << "Longest span (attendu : " << UINT_MAX << ") -> " << extremes.longestSpan() << std::endl;
    }

    std::cout << "\n===== 4. AJOUT PAR PLAGE DEPUIS STD::LIST =====" << std::endl;
    {
        try {
            Span sp(5);
            std::list<int> lst;
            lst.push_back(150);
            lst.push_back(20);
            lst.push_back(420);
			lst.push_back(80);
			lst.push_back(230);

            // Remplissage depuis une liste
            sp.addNumber(lst.begin(), lst.end());

            std::cout << "Shortest span (attendu : 60) -> " << sp.shortestSpan() << std::endl;
            std::cout << "Longest span (attendu : 400) -> " << sp.longestSpan() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << "Exception caught : " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 5. NOMBRES NEGATIFS =====" << std::endl;
    {
        Span sp(3);
		int values[] = {0, 30, -20};

		sp.addNumber(values, values + 3);

        std::cout << "Shortest span(attendu : 20) -> " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span(attendu : 50) -> " << sp.longestSpan() << std::endl;
    }

    std::cout << "\n===== 6. GESTION DES EXCEPTIONS =====" << std::endl;
    // Test 1: Span plein
    try {
        std::cout << "-> Test ajout au-dela de la limite N... ";
        Span sp(2);
        sp.addNumber(42);
        sp.addNumber(3);
        sp.addNumber(11);
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
