#ifndef WHATEVER_HPP
#define WHATEVER_HPP

/**
 * Un template n'est pas du code compilé, c'est un patron que le compilateur
 * utilise pour générer du vrai code à chaque fois qu'un type concret est utilisé
 * — c'est pour ça que toute l'implémentation doit être visible dans le header,
 * sinon le compilateur n'a pas la recette sous la main au moment de générer le
 * code.
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
