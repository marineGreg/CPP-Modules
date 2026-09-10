#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <stdexcept>


/**
 * Recherche la première occurrence d'un entier dans un conteneur modifiable.
 *
 * Cette fonction peut être utilisée avec un conteneur fournissant les méthodes
 * begin() et end(), comme std::vector, std::list ou std::deque.
 *
 * @tparam T Type du conteneur.
 * @param container Conteneur dans lequel effectuer la recherche.
 * @param value Entier recherché.
 *
 * @return Un itérateur vers la première occurrence de value.
 *
 * @throws std::runtime_error Si value n'est pas présent dans le conteneur.
 */
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

/**
 * Recherche la première occurrence d'un entier dans un conteneur constant.
 *
 * Cette surcharge permet d'utiliser easyfind avec un conteneur const.
 * Elle renvoie un const_iterator afin d'empêcher toute modification
 * de l'élément trouvé.
 *
 * @tparam T Type du conteneur.
 * @param container Conteneur constant dans lequel effectuer la recherche.
 * @param value Entier recherché.
 *
 * @return Un itérateur constant vers la première occurrence de value.
 *
 * @throws std::runtime_error Si value n'est pas présent dans le conteneur.
 */
template <typename T>
typename T::const_iterator easyfind(const T &container, int value)
{
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);

    if (it == container.end())
        throw std::runtime_error("Element non trouve dans le conteneur");
    return it;
}

#endif
