#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main()
{
    std::cout << "===== 1. TEST AVEC STD::VECTOR =====" << std::endl;
    {
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        // Test au milieu
        try {
            std::vector<int>::iterator it = easyfind(vec, 30);
            std::cout << "[OK] Valeur trouvee: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }

        // Test au début (premier élément)
        try {
            std::vector<int>::iterator it = easyfind(vec, 10);
            std::cout << "[OK] Premier element trouve: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }

        // Test à la fin (dernier élément)
        try {
            std::vector<int>::iterator it = easyfind(vec, 40);
            std::cout << "[OK] Dernier element trouve: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }

        // Test valeur inexistante
        try {
            std::cout << "Recherche d'une valeur inexistante (99)... ";
            easyfind(vec, 99);
            std::cout << "[KO] Aucune exception levee !" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[OK] Exception attrapee: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 2. TEST DOUBLONS & PREMIERE OCCURRENCE =====" << std::endl;
    {
        std::vector<int> vec;
        vec.push_back(5);
        vec.push_back(42); // Première occurrence de 42 à l'index 1
        vec.push_back(100);
        vec.push_back(42); // Deuxième occurrence de 42 à l'index 3

        try {
            std::vector<int>::iterator it = easyfind(vec, 42);
            std::cout << "Valeur trouvee: " << *it << std::endl;

            // On modifie la valeur via l'itérateur pour vérifier qu'il pointe sur la PREMIÈRE occurrence
            *it = 999;
            std::cout << "Apres modification via itérateur, premier element = " << vec[1] 
                      << " (second element = " << vec[3] << ")" << std::endl;
            if (vec[1] == 999 && vec[3] == 42)
                std::cout << "[OK] C'est bien la premiere occurrence qui a ete modifiee !" << std::endl;
            else
                std::cout << "[KO] Ce n'est pas la premiere occurrence !" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 3. TEST AVEC STD::LIST =====" << std::endl;
    {
        std::list<int> lst;
        lst.push_back(-10);
        lst.push_back(0);
        lst.push_back(100);

        try {
            std::list<int>::iterator it = easyfind(lst, 0);
            std::cout << "[OK] Valeur trouvee dans la liste: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 4. TEST AVEC STD::DEQUE =====" << std::endl;
    {
        std::deque<int> deq;
        deq.push_back(7);
        deq.push_back(14);
        deq.push_back(21);

        try {
            std::deque<int>::iterator it = easyfind(deq, 14);
            std::cout << "[OK] Valeur trouvee dans la deque: " << *it << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[KO] Exception: " << e.what() << std::endl;
        }
    }

    std::cout << "\n===== 5. TEST CONTENEUR VIDE =====" << std::endl;
    {
        std::vector<int> emptyVec;
        try {
            std::cout << "Recherche dans un vector vide... ";
            easyfind(emptyVec, 42);
            std::cout << "[KO] Aucune exception levee !" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "[OK] Exception attrapee: " << e.what() << std::endl;
        }
    }

    return 0;
}
