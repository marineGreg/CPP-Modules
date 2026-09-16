#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <vector>
# include <deque>
# include <string>
# include <algorithm>

/**
 * Trie une séquence d'entiers positifs avec l'algorithme
 * de tri fusion-insertion de Ford-Johnson.
 *
 * Le même algorithme template est instancié pour :
 * - std::vector<int>
 * - std::deque<int>
 *
 * Le programme mesure séparément le temps de traitement
 * obtenu pour les deux conteneurs.
 */
class PmergeMe
{
	private:
        std::vector<int> _vector;
        std::deque<int>  _deque;

        static size_t _getJacobsthal(size_t n);

		void _parseInput(int ac, char **av, std::vector<int> &input) const;

        template <typename Container>
        void _sortContainer(Container& container);

        void _printSequence(
            const std::string& label,
            const std::vector<int>& sequence
        ) const;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void run(int ac, char** av);
};

template <typename Container>
void PmergeMe::_sortContainer(Container &container)
{
    if (container.size() <= 1)
        return;

    // Retrait temporaire du dernier élément si la taille est impaire.
    const bool isOdd = (container.size() % 2 != 0);
    int lastElement = 0;

    if (isOdd)
    {
        lastElement = container.back();
        container.pop_back();
    }

    /*
     * Formation des paires dans deux conteneurs parallèles :
     *
     * highs[i] est le plus grand élément de la paire ;
     * lows[i] est le plus petit élément de la même paire.
     */
    Container highs;
    Container lows;

    for (size_t i = 0; i < container.size(); i += 2)
    {
        int high = container[i];
        int low = container[i + 1];

        if (high < low)
            std::swap(high, low);

        highs.push_back(high);
        lows.push_back(low);
    }

    // Tri récursif des plus grands éléments.
    Container mainChain = highs;

    _sortContainer(mainChain);

    /*
     * Réorganisation des petits éléments afin de conserver
     * leur association avec les grands éléments triés.
     */
    Container pending;
    Container used(highs.size(), 0);

    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < highs.size(); ++j)
        {
            if (!used[j] && highs[j] == mainChain[i])
            {
                pending.push_back(lows[j]);
                used[j] = 1;
                break;
            }
        }
    }
	// La chaîne principale contient déjà les grands éléments triés.
	Container sorted = mainChain;

	/*
	 * partnerIds est un conteneur parallèle à sorted.
	 *
	 * Un entier positif ou nul identifie un grand élément a_i.
	 * La valeur -1 représente un petit élément déjà inséré.
	 *
	 * Cela permet de retrouver la position exacte du grand élément
	 * associé à chaque pending[i], même en présence de doublons.
	 */
	Container partnerIds;

	for (size_t i = 0; i < mainChain.size(); ++i)
    	partnerIds.push_back(static_cast<int>(i));

	/*
 	 * pending[0] correspond à b1.
	 * Comme b1 <= a1, il peut être placé directement au début.
	 */
	if (!pending.empty())
	{
    	sorted.insert(sorted.begin(), pending[0]);
    	partnerIds.insert(partnerIds.begin(), -1);
	}

	// Insertion des autres éléments selon Jacobsthal.
	size_t previousJacobsthal = 1;
	size_t jacobsthalIndex = 3;

	while (previousJacobsthal < pending.size())
	{
    	const size_t nextJacobsthal =
        _getJacobsthal(jacobsthalIndex);

    	const size_t limit =
        std::min(nextJacobsthal, pending.size());

    	for (size_t i = limit; i > previousJacobsthal; --i)
    	{
        	const size_t pendingIndex = i - 1;
        	const int value = pending[pendingIndex];

        	/*
        	 * Recherche de la position actuelle du grand élément
        	 * associé à pending[pendingIndex].
        	 */
        	size_t partnerPosition = 0;

        	while (partnerIds[partnerPosition] != static_cast<int>(pendingIndex))
        	{
            	++partnerPosition;
        	}

        	/*
        	 * La recherche binaire s'arrête avant le grand partenaire.
        	 *
        	 * On sait déjà que :
        	 * pending[pendingIndex] <= grand partenaire
        	 *
        	 * Il serait donc inutile de chercher après lui.
        	 */
        	typename Container::iterator position =
            	std::lower_bound(sorted.begin(), sorted.begin() + partnerPosition, value);

        	/*
        	 * L'indice doit être mémorisé avant insert(), car insert()
        	 * peut invalider l'itérateur position pour un vector.
        	 */
        	const size_t insertionPosition = position - sorted.begin();

        	sorted.insert(position, value);

        	/*
        	 * Mise à jour du conteneur parallèle.
        	 * -1 indique que cet élément n'est pas un grand partenaire.
        	 */
        	partnerIds.insert(partnerIds.begin() + insertionPosition, -1);
    		}
    	previousJacobsthal = nextJacobsthal;
    	++jacobsthalIndex;
	}
    // Réinsertion de l'élément impair éventuel.
    if (isOdd)
    {
        typename Container::iterator position =
            std::lower_bound(sorted.begin(), sorted.end(), lastElement);
        sorted.insert(position, lastElement);
    }
    container = sorted;
}

#endif
