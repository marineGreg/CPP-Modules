
#include "Harl.hpp"

int	main()
{
	Harl harl;

	std::cout << "=== Test 1: All level ===" << std::endl;
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");

	std::cout << "\n=== Test 2: Harl complains about DEBUG ===" << std::endl;
	for (int i = 0; i < 3; i++)
		harl.complain("DEBUG");

	std::cout << "\n=== Test 3: Harl is really angry (ERROR) ===" << std::endl;
	for (int i = 0; i < 5; i++)
		harl.complain("ERROR");

	std::cout << "\n=== Test 4: Several complains ===" << std::endl;
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("DEBUG");
	harl.complain("ERROR");
	harl.complain("INFO");
	harl.complain("WARNING");

	return (0);
}
