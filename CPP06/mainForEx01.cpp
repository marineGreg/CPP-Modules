#include "Bureaucrat.hpp"
#include "Form.hpp"

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define CYAN	"\033[36m"
#define BOLD	"\033[1m"

int main()
{
	std::cout << BOLD << BLUE << "--- Test 1: Valid Form Creation & Output ---" << RESET << std::endl;
	try
	{
		Form tax("Tax Form 1040", 50, 20);
		std::cout << GREEN <<"[SUCCESS] " << RESET << "Created -> " << tax << std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << RED << "[ERROR] " << e.what() << RESET << std::endl;
	}




	std::cout << "\n" << BOLD << BLUE << "--- Test 2: Invalid Form Creation (Exception) ---" << RESET << std::endl;
	try
	{
		std::cout << YELLOW <<"[WARNING] " << RESET << "Attempting to create form with GradeToSign = 0..." << std::endl;
		Form topSecret("Top Secret", 0, 50);
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[EXPECTED ERROR] Exception caught: " << e.what() << RESET << std::endl;
	}

	try
	{
		std::cout << YELLOW <<"[WARNING] " << RESET << "Attempting to create form with GradeToExecute = 151..." << std::endl;
		Form topSecret("Trash Form", 50, 151);
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[EXPECTED ERROR] Exception caught: " << e.what() << RESET << std::endl;
	}




	std::cout << "\n" << BOLD << BLUE << "--- Test 3: Successful Signing ---" << RESET << std::endl;
	try
	{
		Bureaucrat boss("The Boss", 1);
		Form contract("Million Dollar Contract", 10, 5);
		std::cout << CYAN <<"[INFO] " << RESET << "Before signature: " << contract <<  std::endl;
		boss.signForm(contract);
		std::cout << GREEN <<"[SUCCESS] " << RESET << "After signature: " << contract <<  std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << BOLD << RED << "[ERROR] " << e.what() << std::endl;
	}




	std::cout << "\n" << BOLD << BLUE << "--- Test 4: Failed Signing (Grade Too Low) ---" << RESET << std::endl;
	try
	{
		Bureaucrat intern("Poor Intern", 150);
		Form nda("Non-Disclosure Agreement", 50, 50);
		std::cout << CYAN <<"[INFO] " << RESET << "Before signature: " << nda <<  std::endl;
		intern.signForm(nda);
		std::cout << CYAN <<"[INFO] " << RESET << "After signature: " << nda <<  std::endl;
	}
	catch (std::exception & e)
	{
		std::cerr << RED << "[FATAL ERROR] " << e.what() << RESET << std::endl;
	}

	return 0;
}