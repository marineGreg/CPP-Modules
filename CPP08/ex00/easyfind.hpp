#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm> // Pour std::find
# include <exception> // Pour std::exception
# include <stdexcept> // Pour std::runtime_error ou std::out_of_range

// Exception personnalisée si l'élément n'est pas trouvé (optionnel mais très propre !)
class NotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Element non trouve dans le conteneur.";
    }
};

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    // On cherche 'value' de container.begin() jusqu'à container.end()
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    // Si std::find atteint la fin (end()), cela signifie que l'élément n'existe pas
    if (it == container.end())
        throw NotFoundException(); // Ou throw std::runtime_error("Element non trouve");

    return it;
}

#endif
