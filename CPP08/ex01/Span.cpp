#include "Span.hpp"

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
    if (_numbers.size() >= _maxSize)
        throw std::out_of_range("Span plein : impossible d'ajouter un nombre.");
    _numbers.push_back(number);
}

int Span::longestSpan() const {
    if (_numbers.size() <= 1)
        throw std::logic_error("Pas assez d'elements pour calculer un span.");

    int minVal = *std::min_element(_numbers.begin(), _numbers.end());
    int maxVal = *std::max_element(_numbers.begin(), _numbers.end());

    return maxVal - minVal;
}

int Span::shortestSpan() const {
    if (_numbers.size() <= 1)
        throw std::logic_error("Pas assez d'elements pour calculer un span.");

    // Créer une copie triée
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    // Initialiser le minSpan avec la différence entre les 2 premiers éléments
    int minSpan = sorted[1] - sorted[0];

    // Comparer les éléments adjacents
    for (size_t i = 1; i < sorted.size() - 1; ++i) {
        int diff = sorted[i + 1] - sorted[i];
        if (diff < minSpan)
            minSpan = diff;
    }

    return minSpan;
}
