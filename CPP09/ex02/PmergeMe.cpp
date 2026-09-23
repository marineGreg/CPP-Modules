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
 * @brief Convertit les arguments en une séquence d'entiers positifs.
 *
 * Un argument peut contenir un ou plusieurs nombres séparés par des
 * espaces. Chaque token est d'abord contrôlé caractère par caractère,
 * puis converti avec strtol afin de détecter les dépassements.
 *
 * @param ac Nombre d'arguments.
 * @param av Tableau des arguments.
 * @param input Vector recevant les entiers validés.
 *
 * @throws std::invalid_argument Si l'entrée est vide ou invalide.
 */
void PmergeMe::_parseInput(int ac, char **av, std::vector<int> &input) const
{
	if (ac < 2)
		throw std::invalid_argument("missing sequence");

	// Efface un éventuel contenu provenant d'un traitement précédent.
	input.clear();

	// Un argument peut contenir plusieurs nombres séparés par des espaces.
	for (int i = 1; i < ac; ++i)
	{
		const std::string argument(av[i]);
		std::istringstream stream(argument);
		std::string token;
		bool hasToken = false;

		while (stream >> token)
		{
			hasToken = true;
			// Vérifie que le token contient exclusivement des chiffres.
			for (std::size_t j = 0; j < token.size(); ++j)
			{
				const unsigned char c = static_cast<unsigned char>(token[j]);
				if (!std::isdigit(c))
					throw std::invalid_argument("invalid integer");
			}
			/*
			 * strtol réalise la conversion après la validation syntaxique.
			 * errno permet de détecter une valeur trop grande pour un long.
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
		// Refuse également les arguments constitués uniquement d'espaces.
		if (!hasToken)
			throw std::invalid_argument("empty argument");
	}
}

/**
 * @brief Construit l'ordre d'insertion Ford-Johnson.
 *
 * Génère les indices des éléments pending selon les bornes de
 * Jacobsthal (1, 3, 5, 11, 21, 43...). Les indices sont ajoutés par groupes 
 * décroissants : b3, b2, b5, b4, b11, b10, etc.
 *
 * pending[0], correspondant à b1, n'est pas inclus puisqu'il est
 * directement placé au début de la chaîne principale.
 * Entre deux bornes, les indices sont ajoutés en ordre décroissant.
 * Les indices stockés commencent à zéro : l'indice 2 représente b3.
 * 
 * @param size Nombre d'éléments présents dans pending.
 * @return Un vector contenant les indices d'insertion, à partir de zéro.
 */
std::vector<size_t> PmergeMe::_buildInsertionOrder(size_t size)
{
    std::vector<size_t> order;

	// Première paire de bornes Jacobsthal utile : 1 puis 3.
    size_t previous = 1;
    size_t current = 3;

    while (previous < size)
    {
		// La dernière borne ne doit pas dépasser la taille de pending.
        size_t upper = current;

        if (upper > size)
            upper = size;

		// Ajout des indices du groupe dans l'ordre décroissant.
        for (size_t i = upper; i > previous; --i)
            order.push_back(i - 1);

		// Construction de la borne Jacobsthal suivante.
        const size_t next = current + 2 * previous;

        previous = current;
        current = next;
    }

    return order;
}

/**
 * @brief Affiche une version lisible d'une séquence.
 *
 * L'affichage est limité aux cinq premiers nombres lorsque la séquence
 * est longue afin d'éviter une sortie gigantesque pendant les tests.
 *
 * @param label Libellé "Before" ou "After".
 * @param sequence Séquence à afficher.
 */
void PmergeMe::_printSequence(const std::string &label, const std::vector<int> &sequence) const
{
	std::cout << label;
	
	// Limite l'affichage sans modifier la séquence.
	std::size_t limit = sequence.size();

	if (limit > 5)
    	limit = 5;

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
 * @brief Coordonne toutes les étapes du programme.
 *
 * Le parsing est effectué une seule fois. Chaque conteneur est ensuite
 * rempli et trié séparément afin de mesurer son propre temps de
 * traitement.
 *
 * Une vérification finale garantit que vector et deque produisent la
 * même séquence et que celle-ci est réellement triée.
 *
 * @param ac Nombre d'arguments.
 * @param av Tableau des arguments.
 */
void PmergeMe::run(int ac, char **av)
{
	std::vector<int> input;

	// Validation commune avant les mesures de performances.
	_parseInput(ac, av, input);
	_printSequence("Before: ", input);

	struct timeval start, end;

	// Mesure du remplissage et du tri du vector.
	gettimeofday(&start, NULL);

	_vector.assign(input.begin(), input.end());
	_sortVector(_vector);

	gettimeofday(&end, NULL);

	const double vectorTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	// Mesure indépendante du remplissage et du tri du deque.
	gettimeofday(&start, NULL);

	_deque.assign(input.begin(), input.end());
	_sortDeque(_deque);

	gettimeofday(&end, NULL);

	const double dequeTime =
		(end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

	// Les deux instanciations du template doivent produire le même résultat.
	if (_vector.size() != _deque.size()
    	|| !std::equal(_vector.begin(), _vector.end(), _deque.begin()))
	{
    	throw std::logic_error("containers results differ");
	}

	// L'égalité des conteneurs ne suffit pas : vérifie aussi l'ordre croissant.
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
