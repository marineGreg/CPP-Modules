#include "Bureaucrat.hpp"

int	main()
{
	std::cout << "--- Test 1: Normal usage ---" << std::endl;
	try
	{
		Bureaucrat jim("Jim Conrad", 2);
		std::cout << jim << std::endl;
		jim.upGrade(); // Devient grade 1
		std::cout << "After upGrade: " << jim << std::endl;
		// Tentative de monter trop haut
		jim.upGrade();
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 2: Invalid creation (too low) ---" << std::endl;
	try
	{
		Bureaucrat slave("Slave", 160);
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 3: Invalid creation (too high) ---" << std::endl;
	try {
		Bureaucrat god("God", 0);
	}
	catch (std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- Test 4: Limits of downGrade ---" << std::endl;
	try
	{
		Bureaucrat bob("Bob", 149);
		std::cout << bob << std::endl;
		bob.downGrade(); // Grade 150
		std::cout << "After decrement: " << bob << std::endl;
		bob.downGrade(); // Doit throw
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught => " << e.what() << std::endl;
	}
	return 0;
}
