#include "Intern.hpp"
#include "Bureaucrat.hpp"

int	main()
{
	Intern someRandomIntern;
	Bureaucrat boss("The Boss", 1);
	AForm *rrf;

	std::cout << "===== TEST 1: Robotomy =====" << std::endl;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	if (rrf) {
		boss.signForm(*rrf);
		boss.executeForm(*rrf);
		delete rrf;
	}

	std::cout << "\n===== TEST 2: Shrubbery =====" << std::endl;
	AForm *scf;
	scf = someRandomIntern.makeForm("shrubbery creation", "Arthur");
	if (scf) {
		boss.signForm(*scf);
		boss.executeForm(*scf);
		delete scf;
	}

	std::cout << "\n===== TEST 3: Inexistant Form =====" << std::endl;
	rrf = someRandomIntern.makeForm("presidential padon", "Intern");
	if (rrf) {
		delete rrf;
	}

	return 0;
}
