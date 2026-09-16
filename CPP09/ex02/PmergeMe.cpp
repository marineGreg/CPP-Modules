#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <sys/time.h>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cerrno>
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

/**
 * Valide les arguments et les convertit en entiers positifs.
 * La fonction rejette :
 *  - les arguments vides
 *  - les caracteres non numeriques
 *  - zero et les nombres negatifs
 * 	- les valeurs superieures a INT_MAX
 */
void PmergeMe::_parseInput(int ac, char **av, std::vector<int> &input) const
{
	if (ac < 2)
		throw std::invalid_argument("missing sequence");

	input.clear();

	// chaque argument peut contenir plusieurs nombres, un flux en extrait donc les tokens
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
			/*
 			 * La syntaxe ayant été vérifiée caractère par caractère, 
			 * strtol() effectue la conversion et permet de détecter
 			 * un dépassement de capacité grâce à errno.
 			 */
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

size_t PmergeMe::_getJacobsthal(size_t n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    size_t previous = 0;
    size_t current = 1;

    for (size_t i = 2; i <= n; ++i)
    {
        const size_t next = current + 2 * previous;

        previous = current;
        current = next;
    }

    return current;
}

/**
 * Affiche une sequence complete lorsqu'elle est courte
 * Pour une grande sequence, seuls les 5 premiers elements sont affiches
 * Les grandes séquences sont abrégées avec [...]
 */
void PmergeMe::_printSequence(const std::string &label, const std::vector<int> &sequence) const
{
	std::cout << label;
	
	const std::size_t limit = sequence.size() > 5 ? 5 : sequence.size();

	for (std::size_t i = 0; i < limit; ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << sequence[i];
	}
	if (sequence.size() > 5)
		std::cout << " [...]";

	std::cout << std::endl;
}

/**
 * Orchestre l'ensemble du programme :
 *  - validation de l'entree
 *  - affichage de la sequence initiale
 *  - remplissage et tri du vector
 *  - remplissage et tri du deque
 *  - comparaison des resultats
 *  - affichage des temps en microsecondes
 */
void PmergeMe::run(int ac, char **av)
{
	std::vector<int> input;

	_parseInput(ac, av, input);
	_printSequence("Before: ", input);

	struct timeval start, end;

	// La mesure inclut le remplissage du conteneur et son tri
	gettimeofday(&start, NULL);

	_vector.assign(input.begin(), input.end());
	_sortContainer(_vector);

	gettimeofday(&end, NULL);

	const double vectorTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	/* Mesure du remplissage et du tri du deque. */
	gettimeofday(&start, NULL);

	_deque.assign(input.begin(), input.end());
	_sortContainer(_deque);

	gettimeofday(&end, NULL);

	const double dequeTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	/* Verification interne : les deux implementations doivent produire le meme resultat */
	if (_vector.size() != _deque.size()
    	|| !std::equal(_vector.begin(), _vector.end(), _deque.begin()))
	{
    	throw std::logic_error("containers results differ");
	}

	for (std::size_t i = 1; i < _vector.size(); ++i)
	{
    	if (_vector[i - 1] > _vector[i])
        	throw std::logic_error("result is not sorted");
	}

	_printSequence("After:  ", _vector);

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : "
		<< std::fixed << std::setprecision(5) << vectorTime << " us" << std::endl;

	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : "
		<< std::fixed << std::setprecision(5) << dequeTime << " us" << std::endl;
}
