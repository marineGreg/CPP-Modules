#include "RPN.hpp"
#include <iostream>

int main(int ac, char** av) {

    if (ac != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    RPN rpn;
    if (!rpn.resolve(av[1])) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
}
