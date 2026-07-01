#include "Intern.hpp"
#include "Bureaucrat.hpp"

int	main()
{
	Intern someRandomIntern;
	Bureaucrat zapp("Zapp Brannigan", 1);
	AForm *rrf;
	AForm *scf;
	AForm *ppf;
	AForm *random;

	std::cout << "===== TEST 1: Intern creates valid forms =====" << std::endl;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	scf = someRandomIntern.makeForm("shrubbery creation", "Mars");
	ppf = someRandomIntern.makeForm("presidential pardon", "Calculon");

	if (rrf) {
		zapp.signForm(*rrf);
		zapp.executeForm(*rrf);
		delete rrf;
	}

	if (scf) {
		delete scf;
	}

	if (ppf) {
		delete ppf;
	}

	std::cout << "\n===== TEST 2: Intern creates invalid form =====" << std::endl;
	random = someRandomIntern.makeForm("random form", "Intern");
	if (random) {
		delete random;
	}

	return 0;
}
