#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::deque<int>  _deque;
	
		void _parseInput(int ac, char **av, std::vector<int> &input) const;

		std::vector<std::size_t> _buildInsertionOrder(std::size_t pendingSize) const;

		void _sortVector(std::vector<int> &sequence);
		void _sortDeque(std::deque<int> &sequence);

		void _printSequence(const std::string &label, const std::vector<int> &sequence) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		bool run(int ac, char **av);
};

#endif
