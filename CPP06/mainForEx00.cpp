#include "Bureaucrat.hpp"

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define BOLD	"\033[1m"

int main()
{
	std::cout << BOLD << BLUE << "--- Testing Valid Bureaucrat ---" << RESET << std::endl;
	try
	{
		Bureaucrat Manager("Manager", 34);
		std::cout << GREEN <<"[SUCCESS] " << RESET << "Created: " << Manager << std::endl;
		Manager.incrementGrade();
		std::cout << GREEN <<"[SUCCESS] " << RESET << "After promotion: " << Manager << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[ERROR] Exception caught: " << e.what() << RESET << std::endl;
	}

	std::cout << "\n" << BOLD << BLUE << "--- Testing GradeTooHighException ---" << RESET << std::endl;
	try
	{
		Bureaucrat ceo("Xaviel Niel", 1);
		std::cout << YELLOW <<"[WARNING] " << RESET << "Created: " << ceo << std::endl;
		std::cout << YELLOW <<"[WARNING] " << RESET << "Attempting to promote CEO..." << ceo << std::endl;
		ceo.incrementGrade();
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[EXPECTED ERROR] Exception caught: " << e.what() << RESET << std::endl;
	}

	std::cout << "\n" << BOLD << BLUE << "--- Testing GradeTooLowException (Instantiation) ---" << RESET << std::endl;
	try
	{
		std::cout << YELLOW << "[WARNING] " << RESET << "Attempting to hire Slacker at grade 151..." << std::endl;
		Bureaucrat slacker("Slacker", 151);
		std::cout << slacker << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[EXPECTED ERROR] Exception caught: " << e.what() << std::endl;
	}
	return 0;
}