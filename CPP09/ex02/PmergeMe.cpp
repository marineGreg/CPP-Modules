#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) { *this = src; }

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other) {
		this->_vec = other._vec;
		this->_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// Get the Jacobsthal number for a given index n
size_t PmergeMe::_getJacobsthal(size_t n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	size_t j0 = 0, j1 = 1, jNext = 1;
	for (size_t i = 2; i <= n; ++i) {
		jNext = j1 + 2 * j0;
		j0 = j1;
		j1 = jNext;
	}
	return jNext;
}

// Tri Ford Johnson pour std::vector
void PmergeMe::_sortVector(std::vector<int> &arr) {
	if (arr.size() <= 1)
		return;

	bool hasStraggler = (arr.size() % 2 != 0);
	int straggler = 0;

	if (hasStraggler) {
		straggler = arr.back();
		arr.pop_back();
	}

	// 1. Paires (a_i, b_i) avec a_i >= b_i
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2) {
        int a = arr[i];
        int b = arr[i + 1];
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    // 2. Tri récursif de la chaîne principale (a_i)
    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    _sortVector(mainChain);

    // 3. Réorganisation des éléments b_i associés
    std::vector<int> pending;
    std::vector<bool> used(pairs.size(), false);
    std::vector<int> S = mainChain;

    for (size_t i = 0; i < mainChain.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == mainChain[i]) {
                pending.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    // 4. Insertion de b_1 au début
    if (!pending.empty())
        S.insert(S.begin(), pending[0]);

    // Insertion des autres b_i selon la suite de Jacobsthal
    size_t lastJacobsthal = 1;
    size_t jacobsthalIdx = 3;

    while (lastJacobsthal < pending.size()) {
        size_t nextJacobsthal = _getJacobsthal(jacobsthalIdx);
        size_t target = std::min(nextJacobsthal, pending.size());

        for (size_t i = target; i > lastJacobsthal; --i) {
            int valToInsert = pending[i - 1];
            std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), valToInsert);
            S.insert(it, valToInsert);
        }

        lastJacobsthal = nextJacobsthal;
        jacobsthalIdx++;
    }

    // 5. Insertion du nombre impair isolé s'il existe
    if (hasStraggler) {
        std::vector<int>::iterator it = std::lower_bound(S.begin(), S.end(), straggler);
        S.insert(it, straggler);
    }

    arr = S;
}

// -----------------------------------------------------------------------------
// Tri Ford-Johnson pour std::deque
// -----------------------------------------------------------------------------
void PmergeMe::_sortDeque(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return;

    bool hasStraggler = (arr.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) {
        straggler = arr.back();
        arr.pop_back();
    }

    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size(); i += 2) {
        int a = arr[i];
        int b = arr[i + 1];
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    _sortDeque(mainChain);

    std::deque<int> pending;
    std::deque<bool> used(pairs.size(), false);
    std::deque<int> S = mainChain;

    for (size_t i = 0; i < mainChain.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == mainChain[i]) {
                pending.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    if (!pending.empty())
        S.push_front(pending[0]);

    size_t lastJacobsthal = 1;
    size_t jacobsthalIdx = 3;

    while (lastJacobsthal < pending.size()) {
        size_t nextJacobsthal = _getJacobsthal(jacobsthalIdx);
        size_t target = std::min(nextJacobsthal, pending.size());

        for (size_t i = target; i > lastJacobsthal; --i) {
            int valToInsert = pending[i - 1];
            std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), valToInsert);
            S.insert(it, valToInsert);
        }

        lastJacobsthal = nextJacobsthal;
        jacobsthalIdx++;
    }

    if (hasStraggler) {
        std::deque<int>::iterator it = std::lower_bound(S.begin(), S.end(), straggler);
        S.insert(it, straggler);
    }

    arr = S;
}

// -----------------------------------------------------------------------------
// Affichage formaté (Before / After)
// -----------------------------------------------------------------------------
void PmergeMe::_printSequence(const std::string& label, const std::vector<int>& seq) const {
    std::cout << label;
    size_t limit = (seq.size() > 5) ? 4 : seq.size();
    for (size_t i = 0; i < limit; ++i) {
        std::cout << seq[i] << (i + 1 < limit ? " " : "");
    }
    if (seq.size() > 5)
        std::cout << " [...]";
    std::cout << std::endl;
}

// -----------------------------------------------------------------------------
// Parsing et exécution avec mesures de temps
// -----------------------------------------------------------------------------
bool PmergeMe::run(int argc, char** argv) {
    struct timeval start, end;

    // --- Mesure 1 : Parsing + Tri std::vector ---
    gettimeofday(&start, NULL);
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.empty())
            return false;
        std::istringstream iss(arg);
        std::string token;
        while (iss >> token) {
            for (size_t j = 0; j < token.length(); ++j) {
                if (!std::isdigit(token[j]))
                    return false;
            }
            char* endPtr;
            long val = std::strtol(token.c_str(), &endPtr, 10);
            if (*endPtr != '\0' || val <= 0 || val > INT_MAX)
                return false;
            _vec.push_back(static_cast<int>(val));
        }
    }
    if (_vec.empty())
        return false;

    _printSequence("Before: ", _vec);

    _sortVector(_vec);
    gettimeofday(&end, NULL);
    double timeVec = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    _printSequence("After:  ", _vec);

    // --- Mesure 2 : Parsing + Tri std::deque ---
    gettimeofday(&start, NULL);
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        std::string token;
        while (iss >> token) {
            long val = std::strtol(token.c_str(), NULL, 10);
            _deq.push_back(static_cast<int>(val));
        }
    }
    _sortDeque(_deq);
    gettimeofday(&end, NULL);
    double timeDeq = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // --- Affichage des temps ---
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(5)
              << timeVec << " us" << std::endl;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << std::fixed << std::setprecision(5)
              << timeDeq << " us" << std::endl;

    return true;
}
