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

    // Constructeur par défaut privé : un Span doit être initialisé avec une taille N
    Span();

public:
    // --- Forme Canonique Orthodoxe ---
    Span(unsigned int N);
    Span(const Span &src);
    Span &operator=(const Span &rhs);
    ~Span();

    // --- Ajout d'un seul élément ---
    void addNumber(int number);

    // --- Ajout d'une plage d'éléments via itérateurs (Template) ---
    template <typename Iterator>
    void addNumber(Iterator begin, Iterator end) {
        // std::distance calcule le nombre d'éléments entre begin et end
        if (_numbers.size() + std::distance(begin, end) > _maxSize) {
            throw std::out_of_range("Span : capacite insuffisante pour ajouter cette plage.");
        }
        // Insertion de la plage entière en un seul appel
        _numbers.insert(_numbers.end(), begin, end);
    }

    // --- Calculs de Span ---
    int shortestSpan() const;
    int longestSpan() const;
};

#endif
