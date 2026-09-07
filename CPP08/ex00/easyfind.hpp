#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm> // Pour std::find
# include <stdexcept> // Pour std::runtime_error

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    // On cherche 'value' de container.begin() jusqu'à container.end()
    typename T::iterator it = std::find(container.begin(), container.end(), value);

    // Si std::find atteint la fin (end()), cela signifie que l'element n'existe pas
    if (it == container.end())
        throw std::runtime_error("Element non trouve dans le conteneur");
    return it;
}

template <typename T>
typename T::const_iterator easyfind(const T &container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw std::runtime_error("Element non trouve dans le conteneur");
    return it;
}

#endif
