#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

/**
 * Ce template de fonction est un patron de parcours générique. 
 * Il permet d'appliquer une opération sur chaque élément d'un tableau, 
 * quel que soit son type. L'implémentation est maintenue dans le header 
 * car le compilateur doit "cloner" cette logique pour chaque combinaison 
 * de type de tableau (T) et de fonction (F) rencontrée lors des appels.
 */
template <typename T, typename F>
void	iter(T *array, size_t const size, F func) {
	if (!array)
        return;
	for (size_t i = 0; i < size; i++) {
		func(array[i]);
	}
}

#endif