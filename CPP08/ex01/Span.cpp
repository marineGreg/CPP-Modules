#include "Span.hpp"

// Constructeur privé par défaut (non accessible)
Span::Span() : _maxSize(0) {}

Span::Span(unsigned int N) : _maxSize(N) {}

Span::Span(const Span &src) : _maxSize(src._maxSize), _numbers(src._numbers) {}

Span &Span::operator=(const Span &rhs)
{
    if (this != &rhs) {
        this->_maxSize = rhs._maxSize;
        this->_numbers = rhs._numbers;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int number)
{
    if (_numbers.size() >= _maxSize) {
        throw std::out_of_range("Span plein : impossible d'ajouter un nouvel element.");
    }
    _numbers.push_back(number);
}

unsigned int Span::longestSpan() const
{
    if (_numbers.size() < 2)
        throw std::logic_error("Span : pas assez d'elements pour calculer un ecart.");

    // Le plus grand écart est max - min (Complexité O(N))
    int minValue = *std::min_element(_numbers.begin(), _numbers.end());
    int maxValue = *std::max_element(_numbers.begin(), _numbers.end());

    return static_cast<unsigned int>(maxValue) - static_cast<unsigned int>(minValue);
}

unsigned int Span::shortestSpan() const
{
    if (_numbers.size() < 2)
        throw std::logic_error("Span : pas assez d'elements pour calculer un ecart.");

    // Copie triée du tableau pour comparer les voisins consécutifs (Complexité O(N log N))
    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    unsigned int minSpan = static_cast<unsigned int>(sorted[1]) - static_cast<unsigned int>(sorted[0]);

    for (std::vector<int>::size_type i = 1; i + 1 < sorted.size(); ++i)
    {
        unsigned int diff = static_cast<unsigned int>(sorted[i + 1]) - static_cast<unsigned int>(sorted[i]);

        if (diff < minSpan)
            minSpan = diff;
    }
    return minSpan;
}
