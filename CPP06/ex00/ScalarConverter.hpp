#ifndef SCALAR_CONVERTER_HPP
#define SCALAR_CONVERTER_HPP

#include <iostream>
#include <string>
#include <cstdlib> // pour strtod
#include <climits> // pour INT_MAX, INT_MIN
#include <iomanip> // pour setprecision
#include <cmath>   // pour isnan, isinf (ou on peut le faire à la main)

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


#endif
