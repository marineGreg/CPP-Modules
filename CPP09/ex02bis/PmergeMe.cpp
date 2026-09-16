#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) {
    *this = src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        this->_vec = other._vec;
        this->_deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::_printSequence(const std::string &label, const std::vector<int> &seq) const 
{
    std::cout << label;
    size_t limit = seq.size();
    if (limit > 5) {
        limit = 4;
    }
    for (size_t i = 0; i < limit; ++i) {
        std::cout << seq[i];
        if (i + 1 < limit) {
            std::cout << " ";
        }
    }
    if (seq.size() > 5) {
        std::cout << " [...]";
    }
    std::cout << std::endl;
}

// Fonction template d'aide au parsing
template <typename Container>
static bool parseContainer(int ac, char **av, Container &container)
{
    for (int i = 1; i < ac; ++i) {
        std::string arg = av[i];
        if (arg.empty()) {
            return false;
        }
        std::istringstream iss(arg);
        std::string token;
        while (iss >> token) {
            for (size_t j = 0; j < token.length(); ++j) {
                if (!std::isdigit(static_cast<unsigned char>(token[j]))) {
                    return false;
                }
            }
            char* endPtr;
            long val = std::strtol(token.c_str(), &endPtr, 10);
            if (*endPtr != '\0' || val <= 0 || val > INT_MAX) {
                return false;
            }
            container.push_back(static_cast<int>(val));
        }
    }
    if (container.empty()) {
        return false;
    }
    return true;
}

bool PmergeMe::run(int ac, char **av)
{
    struct timeval start, end;

    // --- Mesure 1 : Vector ---
    gettimeofday(&start, NULL);
    if (!parseContainer(ac, av, _vec)) {
        return false;
    }
    _printSequence("Before: ", _vec);

    fordJohnson(_vec);
    gettimeofday(&end, NULL);
    double timeVec = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    _printSequence("After:  ", _vec);

    // --- Mesure 2 : Deque ---
    gettimeofday(&start, NULL);
    parseContainer(ac, av, _deq);
    fordJohnson(_deq);
    gettimeofday(&end, NULL);
    double timeDeq = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    // --- Affichage des résultats ---
    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << std::fixed << std::setprecision(5)
              << timeVec << " us" << std::endl;

    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << std::fixed << std::setprecision(5)
              << timeDeq << " us" << std::endl;

    return true;
}
