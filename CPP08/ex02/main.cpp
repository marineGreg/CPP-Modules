#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main()
{
    std::cout << "=== TEST AVEC MUTANTSTACK ===" << std::endl;
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << "Top: " << mstack.top() << std::endl; // Doit afficher 17

    mstack.pop();

    std::cout << "Size: " << mstack.size() << std::endl; // Doit afficher 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    // Test d'interopérabilité avec std::stack
    std::stack<int> s(mstack);


    std::cout << "\n=== MEME TEST AVEC STD::LIST (RÉSULTATS IDENTIQUES ATTENDUS) ===" << std::endl;
    std::list<int> lstack;

    lstack.push_back(5);
    lstack.push_back(17);

    std::cout << "Top (back): " << lstack.back() << std::endl;

    lstack.pop_back();

    std::cout << "Size: " << lstack.size() << std::endl;

    lstack.push_back(3);
    lstack.push_back(5);
    lstack.push_back(737);
    lstack.push_back(0);

    std::list<int>::iterator lit = lstack.begin();
    std::list<int>::iterator lite = lstack.end();

    ++lit;
    --lit;
    while (lit != lite)
    {
        std::cout << *lit << std::endl;
        ++lit;
    }

    return 0;
}
