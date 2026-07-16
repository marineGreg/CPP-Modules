#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void	iter(T *array, size_t const size, F func) {
	if (!array)
        return;
	for (size_t i = 0; i < size; i++) {
		func(array[i]);
	}
}


#endif