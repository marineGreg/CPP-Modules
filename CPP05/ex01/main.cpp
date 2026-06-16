#include "Bureaucrat.hpp"

int	main()
{
	// Test 1 : Creation valide
	try {
		Bureaucrat jim("Jim Conrad", 2);
		std::cout << jim << std::endl;
	
		jim.incrementGrade();
		std::cout << "After increment: " << jim << std::endl;
	
		jim.incrementGrade();
	} catch (std::exception &e) {
		std::cerr << "Exception caught => " << e.what() << std::endl;
	}

	std::cout << "------" << std::endl;

	// Test 2 : Creation invalide
	try {
		Bureaucrat slave("Slave", 151);
	} catch (std::exception &e) {
		std::cerr << "Exception caught => " << e.what() << std::endl;
	}

	std::cout << "------" << std::endl;

	try {
		Bureaucrat low("Low level", 149);
		std::cout << low << std::endl;
		low.decrementGrade();
		std::cout << "After decrement: " << low << std::endl;
		low.decrementGrade();
	} catch (std::exception &e) {
		std::cerr << "Exception caught => " << e.what() << std::endl;
	}
	return 0;
}
