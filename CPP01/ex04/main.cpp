
#include <iostream>

void	run_replace(std::string filename, std::string s1, std::string s2);

int	main(int ac, char **av)
{
	if (ac != 4) {
		std::cerr << "Usage: ./replace <filename> <string1> <string2>" << std::endl;
		return (1);
	}
	std::string	filename = av[1];
	std::string	s1 = av[2];
	std::string s2 = av[3];

	if (s1.empty()) {
		std::cerr << "Error: string1 cannot be empty" << std::endl;
		return (1);
	}
	run_replace(filename, s1, s2);
	return (0);
}
