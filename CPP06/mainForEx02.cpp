#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define CYAN	"\033[36m"
#define BOLD	"\033[1m"

int main()
{
	std::srand(time(NULL));

	std::cout << BOLD << BLUE << "--- Hiring Bureaucrats ---" << RESET << std::endl;
	Bureaucrat boss("The Boss", 1);
	Bureaucrat midTier("Mid-Tier Mark", 40);
	Bureaucrat intern("Poor intern", 150);
	std::cout << boss << "\n" << midTier << "\n" << intern << std::endl;


	std::cout << "\n" << BOLD << BLUE << "--- Creating Forms ---" << RESET << std::endl;
	ShrubberyCreationForm shrub("Garden");
	RobotomyRequestForm robot("Bender");
	PresidentialPardonForm pardon("Nile");
	std::cout << shrub << "\n" << robot << "\n" << pardon << std::endl;

	std::cout << "\n" << BOLD << BLUE << "--- Test 1: The Intern attempts to do things (should fail) ---" << RESET << std::endl;
	intern.executeForm(shrub);
	intern.signForm(shrub);

	std::cout << "\n" << BOLD << BLUE << "--- Test 2: Mid-Tier executes Shrubbery and Robotomy ---" << RESET << std::endl;
	boss.signForm(shrub);
	boss.signForm(robot);

	midTier.executeForm(shrub);
	midTier.executeForm(robot);

	std::cout << "\n" << BOLD << BLUE << "--- Test 3: Mid-Tier attempts Presidential Pardon (Should Fail) ---" << RESET << std::endl;
	boss.signForm(pardon);
	midTier.executeForm(pardon);

	std::cout << "\n" << BOLD << BLUE << "--- Test 4: The boss steps in (should Success) ---" << RESET << std::endl;
	boss.executeForm(pardon);

	return 0;
}