#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <ctime>

int	main()
{
	std::srand(std::time(NULL));

	std::cout << "===== TEST 1: Presidential Pardon =====" << std::endl;
	try {
			Bureaucrat president("President", 6);
			PresidentialPardonForm pardon("Collin");

			std::cout << president << std::endl;
			std::cout << pardon << std::endl;

			president.signForm(pardon);

			std::cout << "\nAttempting execution with grade 6..." << std::endl;
			president.executeForm(pardon);

			std::cout << "\nPromoting president..." << std::endl;
			president.upGrade();
			std::cout << president << std::endl;

			president.executeForm(pardon);
	}
	catch (std::exception &e) {
			std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 2: Robotomy Request =====" << std::endl;
	try {
			Bureaucrat musk("Elon Musk", 46);
			RobotomyRequestForm	neuralink("Human Brain");

			std::cout << musk << std::endl;
			std::cout << neuralink << std::endl;

			musk.signForm(neuralink);

			std::cout << "\nAttempting execution with grade 46..." << std::endl;
			musk.executeForm(neuralink);

			std::cout << "\nMusk buys some more XP..." << std::endl;
			musk.upGrade();
			std::cout << musk << std::endl;

			std::cout << "\nAttempting robotomy again..." << std::endl;
			for (int i = 0; i < 5; i++){
				std::cout << "Attempt #" << i + 1 << ":" << std::endl;
				musk.executeForm(neuralink);
				std::cout << "---" << std::endl;
			}
	}
	catch (std::exception &e){
		std::cout << "Musky Error: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 3: Shrubbery Creation =====" << std::endl;
	try {
			
			Bureaucrat arthur("King Arthur", 138); // Grade requis : Signer 145, Executer 137
			ShrubberyCreationForm forest("camelot"); // Un point trop bas pour exécuter

			std::cout << arthur << std::endl;
			std::cout << forest << std::endl;

			// 1. Arthur essaie de signer (138 < 145, ça passe !)
			arthur.signForm(forest);

			std::cout << "\nArthur tries to plant the shrubbery..." << std::endl;
			arthur.executeForm(forest);
			arthur.upGrade();
			std::cout << arthur << std::endl;
			arthur.executeForm(forest);
			std::cout << "\nCheck in your folder for a file named 'camelot_shrubbery'!" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
