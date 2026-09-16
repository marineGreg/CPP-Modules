#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <vector>
# include <deque>
# include <string>
# include <algorithm>

/**
 * Trie une séquence d'entiers positifs avec l'algorithme de tri
 * fusion-insertion de Ford-Johnson.
 *
 * Le même algorithme est implémenté séparément avec :
 * - std::vector
 * - std::deque
 *
 * Le programme mesure ensuite le temps de traitement obtenu pour les deux conteneurs.
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

    // Le premier petit élément est nécessairement inférieur au premier grand élément.
    if (!pending.empty())
        sorted.insert(sorted.begin(), pending[0]);

    // Insertion des autres éléments selon Jacobsthal.
    size_t previousJacobsthal = 1;
    size_t jacobsthalIndex = 3;

    while (previousJacobsthal < pending.size())
    {
        const size_t nextJacobsthal = _getJacobsthal(jacobsthalIndex);

        const size_t limit = std::min(nextJacobsthal, pending.size());

        for (size_t i = limit; i > previousJacobsthal; --i)
        {
            const int value = pending[i - 1];

            typename Container::iterator position =
                std::lower_bound(sorted.begin(), sorted.end(), value);
            sorted.insert(position, value);
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
