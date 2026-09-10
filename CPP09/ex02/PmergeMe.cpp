#include "PmergeMe.hpp"

#include <iostream>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <sys/time.h>

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

std::vector<std::size_t> PmergeMe::_buildInsertionOrder(std::size_t size) const
{
	std::vector<std::size_t> order;
	std::size_t previousJacobsthal = 1;
	std::size_t currentJacobsthal = 3;

	while (previousJacobsthal < size)
	{
		const std::size_t upper = std::min(currentJacobsthal, size);
		for (std::size_t i = upper; i > previousJacobsthal; --i)
			order.push_back(i - 1);

		const std::size_t nextJacobsthal = currentJacobsthal + 2 * previousJacobsthal;

		previousJacobsthal = currentJacobsthal;
		currentJacobsthal = nextJacobsthal;
	}
	return order;
}

/**
 * Tri d'un vecteur en utilisant l'algorithme de Ford-Johnson
 */
void PmergeMe::_sortVector(std::vector<int> &sequence)
{
	if (sequence.size() <= 1)
		return;

	const bool isOdd = sequence.size() % 2 != 0;
	int lastElement = 0;

	if (isOdd)
	{
		lastElement = sequence.back();
		sequence.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (std::size_t i = 0; i < sequence.size(); i += 2)
	{
		int hight = sequence[i];
		int low = sequence[i + 1];

		if (hight < low)
			std::swap(hight, low);

		pairs.push_back(std::make_pair(hight, low));
	}
	/**
 	* On extrait les plus grands elements de chaque paire et on les stocke dans un vecteur
 	* Ils sont triés recursivement avec Ford-Johnson
 	*/
	std::vector<int> maxima;

	for (std::size_t i = 0; i < pairs.size(); ++i)
		maxima.push_back(pairs[i].first);

	_sortVector(maxima);

	/**
	 * On reorganise les paires en suivant l'ordre obtenu pour les maxima
	 * Le tableau used permet de gerer correctement les doublons
	 */
	std::vector<std::pair<int, int> > sortedPairs;
	std::vector<bool> used(pairs.size(), false);

	for (std::size_t i = 0; i < maxima.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == maxima[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	pairs = sortedPairs;

	/**
	 * Construction initiale de la sequence triee avec les plus grands elements de chaque paire
	 * 
	 * mainChain = b1, a1, a2, a3 ...
	 * pending = b1, b2, b3 ...
	 * 
	 * b1 est deja dans la mainChain, on commence donc a inserer a1, puis b2, puis a2, puis b3, puis a3 ...
	 */

	std::vector<int> mainChain;
	std::vector<int> pending;
	std::vector<std::size_t> partnerPositions;

	mainChain.push_back(pairs[0].second);

	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		mainChain.push_back(pairs[i].first);
		partnerPositions.push_back(mainChain.size() - 1);
		pending.push_back(pairs[i].second);
	}

	if (isOdd)
		pending.push_back(lastElement);
	
	const std::vector<std::size_t> order = _buildInsertionOrder(pending.size());

	for (std::size_t i = 0; i < order.size(); ++i)
	{
		const std::size_t index = order[i];
		std::size_t searchEnd = mainChain.size();

		/**
		 * Si l'element possede un partenaire a_i, on ne cherche que dans la
		 * partie precedant a_i
		 * 
		 * Le lastElement n'a pas de partenaire, sa borne est donc la fin
		 * de la mainChain
		 */
		if (index < partnerPositions.size())
			searchEnd = partnerPositions[index];

		std::vector<int>::iterator position = 
			std::lower_bound(mainChain.begin(), mainChain.begin() + searchEnd, pending[index]);

		const std::size_t insertPosition = position - mainChain.begin();

		mainChain.insert(position, pending[index]);

		/* Une insertion peut decaler les positions des maxima servant de bornes */
		for (std::size_t j = 0; j < partnerPositions.size(); ++j)
		{
			if (partnerPositions[j] >= insertPosition)
				++partnerPositions[j];
		}
	}
	sequence = mainChain;
}

/**
 * Tri d'une deque en utilisant l'algorithme de Ford-Johnson
 */
void PmergeMe::_sortDeque(std::deque<int> &sequence)
{
	if (sequence.size() <= 1)
		return;

	const bool isOdd = sequence.size() % 2 != 0;
	int lastElement = 0;

	if (isOdd)
	{
		lastElement = sequence.back();
		sequence.pop_back();
	}

	std::deque<std::pair<int, int> > pairs;
	for (std::size_t i = 0; i < sequence.size(); i += 2)
	{
		int hight = sequence[i];
		int low = sequence[i + 1];

		if (hight < low)
			std::swap(hight, low);

		pairs.push_back(std::make_pair(hight, low));
	}
	
	std::deque<int> maxima;

	for (std::size_t i = 0; i < pairs.size(); ++i)
		maxima.push_back(pairs[i].first);

	_sortDeque(maxima);

	std::deque<std::pair<int, int> > sortedPairs;
	std::deque<bool> used(pairs.size(), false);

	for (std::size_t i = 0; i < maxima.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == maxima[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	pairs = sortedPairs;

	std::deque<int> mainChain;
	std::deque<int> pending;
	std::deque<std::size_t> partnerPositions;

	mainChain.push_back(pairs[0].second);

	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		mainChain.push_back(pairs[i].first);
		partnerPositions.push_back(mainChain.size() - 1);
		pending.push_back(pairs[i].second);
	}

	if (isOdd)
		pending.push_back(lastElement);
	
	const std::vector<std::size_t> order = _buildInsertionOrder(pending.size());

	for (std::size_t i = 0; i < order.size(); ++i)
	{
		const std::size_t index = order[i];
		std::size_t searchEnd = mainChain.size();

		if (index < partnerPositions.size())
			searchEnd = partnerPositions[index];

		std::deque<int>::iterator position = 
			std::lower_bound(mainChain.begin(), mainChain.begin() + searchEnd, pending[index]);

		const std::size_t insertPosition = position - mainChain.begin();

		mainChain.insert(position, pending[index]);

		for (std::size_t j = 0; j < partnerPositions.size(); ++j)
		{
			if (partnerPositions[j] >= insertPosition)
				++partnerPositions[j];
		}
	}
	sequence = mainChain;
}

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

void PmergeMe::run(int ac, char **av)
{
	std::vector<int> input;

	_parseInput(ac, av, input);
	_printSequence("Before: ", input);

	struct timeval start, end;

	/* Mesure du remplissage et du tri du vector */
	gettimeofday(&start, NULL);

	_vector.assign(input.begin(), input.end());
	_sortVector(_vector);

	gettimeofday(&end, NULL);

	const double vectorTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	/* Mesure du remplissage et du tri du deque. */
	gettimeofday(&start, NULL);

	_deque.assign(input.begin(), input.end());
	_sortDeque(_deque);

	gettimeofday(&end, NULL);

	const double dequeTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	/* Verification interne : les deux implementations doivent produire le meme resultat */
	if (_vector.size() != _deque.size() || !std::equal(_vector.begin(), _vector.end(), _deque.begin()))
		throw std::logic_error("containers results differ");

	_printSequence("After:  ", _vector);

	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : "
		<< std::fixed << std::setprecision(5) << vectorTime << " us" << std::endl;

	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : "
		<< std::fixed << std::setprecision(5) << dequeTime << " us" << std::endl;
}

