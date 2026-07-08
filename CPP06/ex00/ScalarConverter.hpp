#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>
#include <cstdlib> // pour strtod
#include <climits> // pour INT_MAX, INT_MIN
#include <iomanip> // pour setprecision

/**
 * Les types char, int, float et double sont tous des types numériques.
 * Ils sont liés par des règles de conversion standards définies par le langage
 * C++. Le static_cast est l'outil le plus sûr pour effectuer ces conversions
 * car il demande au compilateur de transformer réellement la valeur
 * (par exemple, tronquer la partie décimale d'un double pour en faire un
 * entier).
 */
class ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter & src);
		ScalarConverter &operator=(const ScalarConverter & other);
		~ScalarConverter();
		
		public:
		static void convert(const std::string & input);
	};
	
	void displayResults(double d);

#endif
