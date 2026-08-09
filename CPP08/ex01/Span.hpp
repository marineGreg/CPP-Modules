#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <exception>
# include <stdexcept>
# include <iterator>

class Span {
private:
    unsigned int        _maxSize;
    std::vector<int>    _numbers;

    Span(); // Constructeur par défaut privé car un Span doit avoir une taille N

public:
    Span(unsigned int N);
    Span(const Span &src);
    Span &operator=(const Span &rhs);
    ~Span();

    void addNumber(int number);

    // Fonction membre template pour ajouter une plage d'itérateurs
    template <typename Iterator>
    void addNumber(Iterator begin, Iterator end) {
        // std::distance calcule le nombre d'éléments entre begin et end
        if (_numbers.size() + std::distance(begin, end) > _maxSize) {
            throw std::out_of_range("Span plein : impossible d'ajouter cette plage.");
        }
        _numbers.insert(_numbers.end(), begin, end);
    }

    int shortestSpan() const;
    int longestSpan() const;
};

#endif
