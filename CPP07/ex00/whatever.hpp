#ifndef WHATEVER_HPP
#define WHATEVER_HPP

/*
 * Les templates doivent être définis dans le header :
 * le compilateur a besoin de voir leur implémentation au moment
 * où il génère la fonction correspondant au type utilisé.
 */

template <typename T>
void	swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
T	min(T const &a, T const &b) {
	if (a < b)
		return a;
	return b;
}

template <typename T>
T	max(T const &a, T const &b) {
	if (a > b)
		return a;
	return b;
}

#endif
