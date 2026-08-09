#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
    std::cout << "=== TEST AVEC STD::VECTOR ===" << std::endl;
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    try {
        std::vector<int>::iterator it = easyfind(vec, 30);
        std::cout << "Valeur trouvee : " << *it << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "Recherche d'une valeur inexistante (99)..." << std::endl;
        easyfind(vec, 99);
    }
    catch (const std::exception &e) {
        std::cerr << "Exception attrapee : " << e.what() << std::endl;
    }

    std::cout << "\n=== TEST AVEC STD::LIST ===" << std::endl;
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    try {
        std::list<int>::iterator it = easyfind(lst, 2);
        std::cout << "Valeur trouvee : " << *it << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
