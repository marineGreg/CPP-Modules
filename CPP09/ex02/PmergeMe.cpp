#include "PmergeMe.hpp"

#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src)
	: _vector(src._vector), _deque(src._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::_parseInput(int ac, char **av, std::vector<int> &input) const
{
	if (ac < 2)
		throw std::invalid_argument("missing sequence");

	input.clear();

	for (int i = 1; i < ac; ++i)
	{
		const std::string argument(av[i]);
		std::istringstream stream(argument);
		std::string token;
		bool hasToken = false;

		while (stream >> token)
		{
			hasToken = true;

			for (std::size_t j = 0; j < token.size(); ++j)
			{
				const unsigned char c = static_cast<unsigned char>(token[j]);
				if (!std::isdigit(c))
					throw std::invalid_argument("invalid integer");
			}

			errno = 0;
			char *end = NULL;
			const long value = std::strtol(token.c_str(), &end, 10);

			if (errno == ERANGE || *end != '\0' || end == token.c_str() 
				|| value <= 0 || value > INT_MAX)
			{
				throw std::invalid_argument("integer out of range");
			}
			input.push_back(static_cast<int>(value));
		}
		if (!hasToken)
			throw std::invalid_argument("empty argument");
	}

}