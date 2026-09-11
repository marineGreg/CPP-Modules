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

/**
 * Construit l'ordre d'insertion des elements pending a partir de la suite Jacobsthal
 * 
 * pending[0], correspondant a b1, est deja place dans la chaine principale
 * il n'apparait donc pas dans l'ordre
 * 
 * L'ordre obtenu commence par : b3, b2, b5, b4, b11, b10, b9, b8, b7, b6...
 */
std::vector<std::size_t> PmergeMe::_buildInsertionOrder(std::size_t size) const
{
	/*
 	 * Les bornes Jacobsthal utiles sont :
 	 * 1, 3, 5, 11, 21, 43...
 	 *
 	 * Entre deux bornes, les indices sont ajoutés en ordre décroissant
	 * afin d'optimiser les recherches binaires.
	 *	
	 * Les indices sont stockés à partir de zéro : l'indice 2 correspond donc à b3.
	 */
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
 * Tri recursivement un vector avec l'algorithme de Ford-Johnson
 * Étapes de Ford-Johnson :
 *
 * 1. regrouper les valeurs par paires
 * 2. comparer les deux éléments de chaque paire
 * 3. trier récursivement les maxima
 * 4. construire une chaîne principale triée
 * 5. insérer les minima dans l'ordre Jacobsthal
 * 6. limiter chaque recherche au partenaire associé
 */
void PmergeMe::_sortVector(std::vector<int> &sequence)
{
	if (sequence.size() <= 1)
		return;

	const bool isOdd = sequence.size() % 2 != 0;
	int lastElement = 0;

	/*
	 * Si le nombre d'éléments est impair, le dernier élément
	 * reste temporairement sans partenaire.
	 * Il rejoindra ensuite la liste pending avec une borne
	 * de recherche située à la fin de la chaîne.
	 */
	if (isOdd)
	{
		lastElement = sequence.back();
		sequence.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (std::size_t i = 0; i < sequence.size(); i += 2)
	{
		int high = sequence[i];
		int low = sequence[i + 1];

		if (high < low)
			std::swap(high, low);

		pairs.push_back(std::make_pair(high, low));
	}
	/**
 	* On extrait les plus grands elements de chaque paire et on les stocke dans un vecteur
 	* Ils sont tries recursivement avec Ford-Johnson
 	*/
	std::vector<int> maxima;

	for (std::size_t i = 0; i < pairs.size(); ++i)
		maxima.push_back(pairs[i].first);

	/*
	 * Ford-Johnson trie recursivement les maxima a_i.
	 * Le cas de base est atteint lorsque la sequence contient zero ou un element.
	 */
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

	/*
	 * Construction de la chaîne principale :
	 * mainChain = b1, a1, a2, a3...
	 * pending   = b1, b2, b3...
	 *
	 * Tous les maxima a_i sont déjà présents et triés.
	 * b1 est également déjà placé devant a1 puisque b1 <= a1.
	 *
	 * Les autres éléments pending seront insérés selon
	 * l'ordre calculé à partir des nombres de Jacobsthal.
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

		/*
		 * b_i est forcément inférieur ou égal à son partenaire a_i.
		 * Il est donc inutile de chercher après ce partenaire.
		 *
		 * lower_bound() travaille uniquement dans l'intervalle :
		 * [début de mainChain, position de a_i[
		 *
		 * L'élément impair n'ayant pas de partenaire, sa recherche
		 * peut aller jusqu'à la fin de la chaîne.
		 */
		std::vector<int>::iterator position = 
			std::lower_bound(mainChain.begin(), mainChain.begin() + searchEnd, pending[index]);

		const std::size_t insertPosition = position - mainChain.begin();

		mainChain.insert(position, pending[index]);

		/*
		 * Insérer une valeur déplace vers la droite tous les maxima
		 * placés à partir de la position d'insertion.
		 *
		 * Leurs indices sont mis à jour afin que les prochaines
		 * recherches conservent leurs bornes correctes.
 		 */
		for (std::size_t j = 0; j < partnerPositions.size(); ++j)
		{
			if (partnerPositions[j] >= insertPosition)
				++partnerPositions[j];
		}
	}
	sequence = mainChain;
}

/**
 * Tri recursivement un deque avec l'algorithme de Ford-Johnson
 * Même deroulement que pour std::vector, mais toutes
 * les structures participant au tri sont des std::deque.
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
		int high = sequence[i];
		int low = sequence[i + 1];

		if (high < low)
			std::swap(high, low);

		pairs.push_back(std::make_pair(high, low));
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

