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
	 * b1 est nécessairement inférieur ou égal à a1.
	 * Il peut donc être inséré directement au début.
	 */
	if (!pending.empty())
	    sorted.insert(sorted.begin(), pending[0]);

	/*
	 * Construction de l'ordre Jacobsthal :
	 * b3, b2, b5, b4, b11, b10...
	 */
	const std::vector<size_t> order = _buildInsertionOrder(pending.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
    	const size_t index = order[i];
    	const int value = pending[index];
    	const int partner = mainChain[index];

    	/*
    	 * Recherche de la première occurrence du grand partenaire.
    	 * L'élément pending[index] ne doit être recherché que dans
    	 * la partie située avant ce partenaire.
    	 */
    	typename Container::iterator upperBound =
        	std::lower_bound(sorted.begin(), sorted.end(), partner);

		typename Container::iterator position =
        	std::lower_bound(sorted.begin(), upperBound, value);

    	sorted.insert(position, value);
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
