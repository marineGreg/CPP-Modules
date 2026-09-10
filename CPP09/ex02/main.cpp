#include "PmergeMe.hpp"

#include <exception>
#include <iostream>

int main(int ac, char **av)
{
	try {
		PmergeMe pmerge;
		pmerge.run(ac, av);
	}
	catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

