#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	std::cout << "===== TEST 1: Successful Signing =====" << std::endl;
	try {
			Bureaucrat boss("The Boss", 10);
			Form contract("Important contract", 20, 45);

			std::cout << boss << std::endl;
			std::cout << contract << std::endl;

			boss.signForm(contract); // Doit réussir car 10 <= 20

			std::cout << contract << std::endl; // Doit être "signed: yes"
	}
	catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 2: Failed Signing (Grade too low) =====" << std::endl;
	try {
			Bureaucrat intern("Intern", 120);
			Form topSecret("Top Secret Document", 50, 10);

			std::cout << intern << std::endl;
			std::cout << topSecret << std::endl;

			intern.signForm(topSecret); // Doit échouer car 120 > 50
	}
	catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 3: Invalid Form Creation (Too High) =====" << std::endl;
	try {
			Form illegal("Illegal Form", 0, 50); // Grade 0 est interdit
	}
	catch (std::exception &e) {
			std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	std::cout << "\n===== TEST 4: Invalid Form Creation (Too Low) =====" << std::endl;
	try {
			Form illegal("Illegal Form", 151, 50); // Grade 151 est interdit
	}
	catch (std::exception &e) {
			std::cerr << "Caught expected error: " << e.what() << std::endl;
	}
	
	std::cout << "\n===== TEST 5: Already Signed Check =====" << std::endl;
	try {
			Bureaucrat boss("The Boss", 1);
			Form paper("Plain Paper", 100, 100);

			boss.signForm(paper);
			boss.signForm(paper);
	}
	catch (std::exception &e) {
		std::cerr << "Note: " << e.what() << std::endl;
	}
	return 0;
}
