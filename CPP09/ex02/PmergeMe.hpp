#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <sstream>
# include <cstdlib>
# include <climits>
# include <sys/time.h>
# include <algorithm>
# include <iomanip>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;
	
		static size_t _getJacobsthal(size_t n);

		void _sortVector(std::vector<int> &arr);
		void _sortDeque(std::deque<int> &arr);

		void printSequence(const std::string &label, const std::vector<int> &seq) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		bool run(int ac, char **av);
};

#endif;
