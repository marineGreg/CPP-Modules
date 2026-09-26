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
 * Le même algorithme est instancié pour :
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

		void _parseInput(int ac, char **av, std::vector<int> &input) const;
		
		void _sortVector(std::vector<int> &container);
		void _sortDeque(std::deque<int> &container);

        static std::vector<size_t> _buildInsertionOrder(size_t size);
		
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

#endif
