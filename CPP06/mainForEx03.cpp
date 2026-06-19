#include "Bureaucrat.hpp"
#include "Intern.hpp"

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"

int main()
{
	Intern someRandomIntern;
	AForm* scf;
	AForm* ppf;
	AForm* rrf;
	AForm* unknow;

	std::cout << GREEN << "--- 1. Intern creating valid forms ---" << RESET << std::endl;
	scf = someRandomIntern.makeForm("shrubbery creation", "Garden");
	ppf = someRandomIntern.makeForm("presidential pardon", "Nile");
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");

	std::cout << "\n" << RED << "--- 2. Intern creating an invalid form ---" << RESET << std::endl;
	unknow = someRandomIntern.makeForm("Vampire Empire", "Stimulation swarm");

	std::cout << "\n" << GREEN << "--- 3. Bureaucrat interacting with dynamically created forms ---" << RESET << std::endl;
	Bureaucrat boss("The boss", 1);
	if (rrf)
	{
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
	}

	delete scf;
	delete ppf;
	delete rrf;
	delete unknow;

	return 0;
}