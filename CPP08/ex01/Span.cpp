#include "Span.hpp"

// Constructeur privé par défaut (non accessible)
Span::Span() : _maxSize(0) {}

Span::Span(unsigned int N) : _maxSize(N) {}

Span::Span(const Span &src) : _maxSize(src._maxSize), _numbers(src._numbers) {}

Span &Span::operator=(const Span &rhs) {
    if (this != &rhs) {
        this->_maxSize = rhs._maxSize;
        this->_numbers = rhs._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number) {
    if (_numbers.size() >= _maxSize) {
        throw std::out_of_range("Span plein : impossible d'ajouter un nouvel element.");
    }
    _numbers.push_back(number);
}

int Span::longestSpan() const {
    if (_numbers.size() <= 1) {
        throw std::logic_error("Span : pas assez d'elements pour calculer un ecart.");
    }

    // Le plus grand écart est max - min (Complexité O(N))
    int minVal = *std::min_element(_numbers.begin(), _numbers.end());
    int maxVal = *std::max_element(_numbers.begin(), _numbers.end());

    return maxVal - minVal;
}

int Span::shortestSpan() const {
    if (_numbers.size() <= 1) {
        throw std::logic_error("Span : pas assez d'elements pour calculer un ecart.");
    }

    // Copie triée du tableau pour comparer les voisins consécutifs (Complexité O(N log N))
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = sorted[1] - sorted[0];

    for (size_t i = 1; i < sorted.size() - 1; ++i) {
        int diff = sorted[i + 1] - sorted[i];
        if (diff < minSpan) {
            minSpan = diff;
        }
    }

    return minSpan;
}
