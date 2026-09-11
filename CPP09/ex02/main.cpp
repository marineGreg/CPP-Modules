#include "PmergeMe.hpp"

#include <exception>
#include <iostream>

int main(int ac, char **av)
{
	try {
		PmergeMe pmerge;
		pmerge.run(ac, av);
	}
	catch (const std::exception &) {
		std::cerr << "Error " << std::endl;
		return 1;
	}
	return 0;
}

