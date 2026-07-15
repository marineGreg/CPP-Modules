#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter & src) { (void)src; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter & other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string & input) {
    // Traitement des cas speciaux (nan, inf) en premier
    if (input == "nan" || input == "nanf") {
        std::cout << "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan" 
		<< std::endl;
    	return;
	}
    if (input == "+inf" || input == "+inff" || input == "-inf" || input == "-inff"
		|| input == "inf" || input == "inff") {
        std::string sign = "";
        if (input[0] == '+')
			sign = "+";
        if (input[0] == '-')
			sign = "-";
        std::cout << "char: impossible\nint: impossible" << std::endl;
        std::cout << "float: " << sign << "inff" << std::endl;
        std::cout << "double: " << sign << "inf" << std::endl;
        return;
    }

    // 2. DETECTION DU TYPE CHAR UNIQUE
    // Si l'input est 'a', ce n'est pas un nombre mais un char.
    if (input.length() == 1 && !std::isdigit(input[0])) {
        char c = input[0];
        displayResults(static_cast<double>(c));
        return;
    }

    // 3. CONVERSION NUMÉRIQUE
    char * endptr;
    // strtod convertit une string en double. endptr pointera sur le reste
    double d = std::strtod(input.c_str(), & endptr);

    // Verification de la validite de la string
    if (*endptr != '\0' && std::string(endptr) != "f") {
        std::cout << "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan" 
		<< std::endl;
        return;
    }

	displayResults(d);
}

void displayResults(double d) {
    // 1. AFFICHAGE CHAR
    std::cout << "char: ";
    if (d < 0 || d > 127 || d != d) // hors limites ou NaN
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(d))) // Pas imprimable (ex: 0 à 31)
        std::cout << "Non displayable" << std::endl;
	else
        std::cout << "'" << static_cast<char>(d) << "'" << std::endl;

    // 2. AFFICHAGE INT
    std::cout << "int: ";
    if (d > INT_MAX || d < INT_MIN || d != d)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(d) << std::endl;

    // 3. AFFICHAGE FLOAT & DOUBLE
    // On force l'affichage d'au moins un ".0" avec fixed et setprecision
    std::cout << "float: " << std::fixed << std::setprecision(1) 
	<< static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}
 