#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <vector>
# include <deque>
# include <string>

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
	
		void _parseInput(int ac, char **av, std::vector<int> &input) const;

		std::vector<std::size_t> _buildInsertionOrder(std::size_t size) const;

		void _sortVector(std::vector<int> &sequence);
		void _sortDeque(std::deque<int> &sequence);

		void _printSequence(const std::string &label, const std::vector<int> &sequence) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void run(int ac, char **av);
};

#endif
