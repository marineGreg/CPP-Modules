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

class PmergeMe {
private:
    std::vector<int> _vec;
    std::deque<int>  _deq;

    static size_t _getJacobsthal(size_t n);
    void _printSequence(const std::string& label, const std::vector<int> &seq) const;

public:
    PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe& operator=(const PmergeMe &other);
    ~PmergeMe();

    bool run(int ac, char **av);
};

// Template pour trier n'importe quel conteneur séquentiel (vector/deque) avec Ford-Johnson
template <typename Container>
void fordJohnson(Container &container) {
    if (container.size() <= 1) {
        return;
    }

    bool isOdd = false;
    if (container.size() % 2 != 0) {
        isOdd = true;
    }

    int lastElement = 0;
    if (isOdd) {
        lastElement = container.back();
        container.pop_back();
    }

    // 1. Formation des paires (a, b) avec a >= b
    typedef typename Container::value_type ValueType;
    typedef std::pair<ValueType, ValueType> PairType;
    std::vector<PairType> pairs;

    for (size_t i = 0; i < container.size(); i += 2) {
        ValueType a = container[i];
        ValueType b = container[i + 1];
        if (a < b) {
            std::swap(a, b);
        }
        pairs.push_back(std::make_pair(a, b));
    }

    // 2. Tri récursif des grands éléments (a)
    Container mainChain;
    for (size_t i = 0; i < pairs.size(); ++i) {
        mainChain.push_back(pairs[i].first);
    }

    fordJohnson(mainChain);

    // 3. Associatons des petits éléments (b) dans l'ordre de la chaîne principale triée
    Container pending;
    std::vector<bool> used(pairs.size(), false);

    for (typename Container::iterator it = mainChain.begin(); it != mainChain.end(); ++it) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == *it) {
                pending.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    Container S = mainChain;

    if (!pending.empty()) {
        S.insert(S.begin(), pending[0]);
    }

    // 4. Insertion binaire ordonnée par les nombres de Jacobsthal
    size_t lastJacobsthal = 1;
    size_t jacobsthalIdx = 3;

    while (lastJacobsthal < pending.size()) {
        size_t nextJacobsthal = 1;
        // Calcul manuel du nombre de Jacobsthal
        if (jacobsthalIdx == 3) nextJacobsthal = 3;
        else if (jacobsthalIdx == 4) nextJacobsthal = 5;
        else if (jacobsthalIdx == 5) nextJacobsthal = 11;
        else if (jacobsthalIdx == 6) nextJacobsthal = 21;
        else if (jacobsthalIdx == 7) nextJacobsthal = 43;
        else if (jacobsthalIdx == 8) nextJacobsthal = 85;
        else if (jacobsthalIdx == 9) nextJacobsthal = 171;
        else if (jacobsthalIdx == 10) nextJacobsthal = 341;
        else if (jacobsthalIdx == 11) nextJacobsthal = 683;
        else if (jacobsthalIdx == 12) nextJacobsthal = 1365;
        else nextJacobsthal = 2731;

        size_t target = pending.size();
        if (nextJacobsthal < target) {
            target = nextJacobsthal;
        }

        for (size_t i = target; i > lastJacobsthal; --i) {
            ValueType valToInsert = pending[i - 1];
            typename Container::iterator pos = std::lower_bound(S.begin(), S.end(), valToInsert);
            S.insert(pos, valToInsert);
        }

        lastJacobsthal = nextJacobsthal;
        jacobsthalIdx++;
    }

    // 5. Insertion de l'élément impair isolé s'il existe
    if (isOdd) {
        typename Container::iterator pos = std::lower_bound(S.begin(), S.end(), lastElement);
        S.insert(pos, lastElement);
    }

    container = S;
}

#endif
