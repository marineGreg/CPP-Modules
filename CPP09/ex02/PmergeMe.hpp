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

        static std::vector<size_t> _buildInsertionOrder(size_t size);
		void _parseInput(int ac, char **av, std::vector<int> &input) const;

		/**
		 * @brief Trie un vector ou un deque avec Ford-Johnson.
		 *
		 * La fonction :
		 *  1. forme des paires ordonnées ;
		 *  2. trie récursivement les plus grands éléments ;
		 *  3. réassocie les petits éléments ;
		 *  4. les insère selon l'ordre de Jacobsthal ;
		 *  5. réinsère l'éventuel élément impair.
		 *
		 * @tparam Container Type du conteneur, vector<int> ou deque<int>.
		 * @param container Conteneur à trier directement.
		 */
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


/**
 * @brief Applique récursivement le tri fusion-insertion.
 * 		  Trie un vector ou un deque avec Ford-Johnson.
 *
 * La fonction :
 *  1. forme des paires ordonnées ;
 *  2. trie récursivement les plus grands éléments ;
 *  3. réassocie les petits éléments ;
 *  4. les insère selon l'ordre de Jacobsthal ;
 *  5. réinsère l'éventuel élément impair.
 *
 * Les éléments sont regroupés par paires. Dans chaque paire, le plus
 * grand élément rejoint la chaîne principale, tandis que le plus petit
 * est conservé dans pending.
 *
 * La chaîne principale est triée récursivement. Les éléments pending
 * sont ensuite insérés par recherche binaire selon l'ordre fourni par
 * la suite de Jacobsthal.
 *
 * @tparam Container Conteneur séquentiel à accès aléatoire.
 * @param container Conteneur modifié directement par la fonction.
 */
template <typename Container>
void PmergeMe::_sortContainer(Container &container)
{
    if (container.size() <= 1)
        return;

    // Mise de côté du dernier élément lorsque la taille est impaire.
    const bool isOdd = (container.size() % 2 != 0);
    int lastElement = 0;

    if (isOdd)
    {
        lastElement = container.back();
        container.pop_back();
    }

	// highs[i] et lows[i] représentent les deux membres d'une même paire.
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

    // Tri récursif des plus grands éléments de chaque paire.
    Container mainChain = highs;

    _sortContainer(mainChain);

    // Replace chaque petit élément dans l'ordre de son grand partenaire.
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
	// La chaîne principale est déjà triée à cette étape.
	Container sorted = mainChain;

	// b1 est inférieur ou égal à a1 : aucune recherche n'est nécessaire.
	if (!pending.empty())
	    sorted.insert(sorted.begin(), pending[0]);

	// Ordre d'insertion selon Jacobsthal : b3, b2, b5, b4, b11, b10...
	const std::vector<size_t> order = _buildInsertionOrder(pending.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
    	const size_t index = order[i];
    	const int value = pending[index];
    	const int partner = mainChain[index];

    	// Limite la recherche à la partie précédant le grand partenaire.
    	typename Container::iterator upperBound =
        	std::lower_bound(sorted.begin(), sorted.end(), partner);

		// Recherche de la position du petit élément dans la zone autorisée.
		typename Container::iterator position =
        	std::lower_bound(sorted.begin(), upperBound, value);

    	sorted.insert(position, value);
	}

    // L'élément impair n'a pas de partenaire : recherche dans toute la chaîne.
    if (isOdd)
    {
        typename Container::iterator position =
            std::lower_bound(sorted.begin(), sorted.end(), lastElement);
        sorted.insert(position, lastElement);
    }
    container = sorted;
}

#endif
