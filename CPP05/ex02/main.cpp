#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <ctime>

int	main()
{
	// Initialisation de l'aléatoire pour la Robotomie
	std::srand(std::time(NULL));

	std::cout << "===== Section 1: Planet Express Staffing =====" << std::endl;
	Bureaucrat zapp("Zapp Brannigan", 1);        // Le général
	Bureaucrat hermes("Hermes Conrad", 37);     // Le bureaucrate pro
	Bureaucrat fry("Philip Fry", 150);       // Le livreur

	std::cout << zapp << std::endl;
	std::cout << hermes << std::endl;
	std::cout << fry << std::endl;

	std::cout << "\n===== Section 2: Galactic Paperwork =====" << std::endl;
	ShrubberyCreationForm marsForest("Mars");
	RobotomyRequestForm unit22("Unit 22");
	PresidentialPardonForm criminal("Calculon");

	std::cout << marsForest << std::endl;
	std::cout << unit22 << std::endl;
	std::cout << criminal << std::endl;


	std::cout << "\n===== Section 3: The Delivery Boy attempts to work =====" << std::endl;
	// Fry est grade 150. Il ne peut rien faire.
	fry.signForm(marsForest);
	fry.executeForm(marsForest);


	std::cout << "\n===== Section 4: Zapp Signs Everything (Authority check) =====" << std::endl;
	// Zapp signe tout car il a le grade 1, mais il n'exécute rien par paresse
	zapp.signForm(marsForest);
	zapp.signForm(unit22);
	zapp.signForm(criminal);

	std::cout << "\n===== Section 5: Hermes performs his duties =====" << std::endl;
	std::cout << "--- Shrubbery execution ---" << std::endl;
	hermes.executeForm(marsForest);  // Shrubbery (exec 137) -> OK

	std::cout << "\n--- Multiple Robotomy attempts (50/50 chance) ---" << std::endl;
	for (int i = 0; i < 5; i++){
		std::cout << "Attempt #" << i + 1 << ":" << std::endl;
		hermes.executeForm(unit22);
		std::cout << "---" << std::endl;
	} // Robotomy (exec 45) -> OK

	std::cout << "\n--- Presidential Pardon attempt ---" << std::endl;
	hermes.executeForm(criminal); // Doit échouer car Hermes est 37 et il faut 5.


	std::cout << "\n===== Section 6: The Ultimate Pardon =====" << std::endl;
	// Zapp doit s'en occuper lui-même
	zapp.executeForm(criminal);


	std::cout << "\n===== Section 7: Unsigned Form execution test =====" << std::endl;
	// On crée un nouveau formulaire non signé
	ShrubberyCreationForm unsignedForm("Void");
	zapp.executeForm(unsignedForm); // Va échouer car non signé

	return 0;
}
