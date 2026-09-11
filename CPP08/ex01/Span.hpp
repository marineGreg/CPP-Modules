#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <algorithm>
# include <stdexcept>
# include <iterator>

/**
 * Stocke un nombre limité d'entiers et calcule les écarts
 * minimum et maximum entre les valeurs enregistrées.
 *
 * Un objet Span possède une capacité maximale fixée lors
 * de sa construction. Tout dépassement lève une exception.
 */
class Span {
private:
    unsigned int        _maxSize; // Capacité maximale du Span
    std::vector<int>    _numbers; // Conteneur pour stocker les entiers

    Span(); // Constructeur par défaut privé : un Span doit être initialisé avec une taille N

public:
    // --- Forme Canonique Orthodoxe ---
    Span(unsigned int N);
    Span(const Span &src);
    Span &operator=(const Span &other);
    ~Span();

    
    void addNumber(int number); // Ajoute un entier au Span

    /**
	 * Permet d'ajouter une plage complète d'entiers au Span.
	 * La fonction prend deux itérateurs représentant le début et la fin de la plage.
	 * 
	 * @tparam Iterator Type des itérateurs fournis.
	 * @param begin Itérateur vers le premier élément.
	 * @param end Itérateur situé après le dernier élément.
	 */
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
    unsigned int longestSpan() const; // Calcule l'écart maximum entre les valeurs stockées
    unsigned int shortestSpan() const; // Calcule l'écart minimum entre les valeurs stockées
};

#endif
