#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter & src) { (void)src; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter & other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string & input) {
    // 1. GESTION DES CAS SPÉCIAUX (Pseudo-littéraux)
    if (input == "nan" || input == "nanf" || input == "+inf" || input == "+inff" || 
        input == "-inf" || input == "-inff") {
        
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        
        // On affiche nanf si c'est un float, nan si c'est un double
        if (input.find("nan") != std::string::npos) {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        } else {
            // Gestion des infinis
            std::string res = (input[0] == '+') ? "+inf" : "-inf";
            std::cout << "float: " << res << "f" << std::endl;
            std::cout << "double: " << res << std::endl;
        }
        return;
    }

    // 2. DÉTECTION DU TYPE CHAR UNIQUE
    // Si l'input est 'a', ce n'est pas un nombre mais un char.
    if (input.length() == 1 && !std::isdigit(input[0])) {
        char c = input[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
        std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
        return;
    }

    // 3. CONVERSION NUMÉRIQUE (Le gros morceau)
    char* endptr;
    // strtod convertit une string en double. endptr pointera sur le reste (ex: le 'f' de 42.0f)
    double d = std::strtod(input.c_str(), &endptr);

    // Vérification sommaire : si on n'a rien lu du tout
    if (input.c_str() == endptr) {
        std::cout << "Error: Invalid input" << std::endl;
        return;
    }

    // --- AFFICHAGE CHAR ---
    if (d < 0 || d > 127) {
        std::cout << "char: impossible" << std::endl;
    } else if (!std::isprint(static_cast<int>(d))) {
        std::cout << "char: Non displayable" << std::endl;
    } else {
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
    }

    // --- AFFICHAGE INT ---
    if (d > INT_MAX || d < INT_MIN) {
        std::cout << "int: impossible" << std::endl;
    } else {
        std::cout << "int: " << static_cast<int>(d) << std::endl;
    }

    // --- AFFICHAGE FLOAT & DOUBLE ---
    // On utilise fixed et setprecision(1) pour forcer le ".0" demandé par le sujet
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}
