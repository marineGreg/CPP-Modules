#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

/**
 * Extension de std::stack ajoutant la possibilité d'itérer
 * sur les éléments de la pile.
 *
 * std::stack est un adaptateur de conteneur : il ne stocke pas
 * directement les éléments, mais s'appuie sur un conteneur interne,
 * généralement un std::deque.
 *
 * MutantStack conserve toutes les opérations classiques d'une stack
 * comme push(), pop(), top(), size() et empty(), puis expose les
 * itérateurs du conteneur interne.
 *
 * @tparam T Type des éléments contenus dans la pile.
 */
template <typename T>
class MutantStack : public std::stack<T> {
public:
    MutantStack();
    MutantStack(const MutantStack &src);
    MutantStack &operator=(const MutantStack &other);
    ~MutantStack();

    // std::stack<T>::container_type fait référence au conteneur sous-jacent (std::deque par défaut)
	// on recupere ici ses quatres types d'itérateurs
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    // Renvoie l'itérateur vers le premier élément de la pile (le plus bas)
    iterator begin();

	// Renvoie l'itérateur marquant le dernier élément de la pile (le plus haut)
    iterator end();

    // Versions constantes de begin() et end().
    const_iterator begin() const;
    const_iterator end() const;

	// Renvoie un itérateur inversé vers le dernier élément de la pile (le plus haut)
    reverse_iterator rbegin();
	// Renvoie un itérateur inversé marquant le premier élément de la pile (le plus bas)
    reverse_iterator rend();

	// Versions constantes de rbegin() et rend().
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
};

// Forme Canonique Orthodoxe (OFC)
template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &src) : std::stack<T>(src) {}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &other) {
    if (this != &other) {
        std::stack<T>::operator=(other);
    }
    return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {}

/*
 * std::stack possède un attribut protégé nommé c.
 * Cet attribut représente le conteneur interne de la pile.
 *
 * Comme MutantStack hérite de std::stack, elle peut accéder à c.
 *
 * Le préfixe this-> est nécessaire ici car std::stack<T> est
 * une classe de base dépendante du paramètre template T.
 */
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
    return this->c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
    return this->c.end();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin() {
    return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend() {
    return this->c.rend();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const {
    return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const {
    return this->c.rend();
}

#endif
