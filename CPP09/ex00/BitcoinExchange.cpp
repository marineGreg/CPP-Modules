#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
    : _dB(src._dB) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _dB = other._dB;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/**
 * Supprime les espaces et caracteres blancs situes au debut et à la fin d'une chaine.
 *
 * @param str Chaine à nettoyer.
 * @return La chaine nettoyee, ou une chaine vide si elle ne contenait que des espaces.
 */
std::string BitcoinExchange::_trim(const std::string &str) const
{
    const std::string whitespace = " \t\r\n";

    std::string::size_type start = str.find_first_not_of(whitespace);

    if (start == std::string::npos)
        return "";

    std::string::size_type end = str.find_last_not_of(whitespace);

    return str.substr(start, end - start + 1);
}

/**
 * Vérifie qu'une date respecte le format YYYY-MM-DD
 * et qu'elle existe réellement dans le calendrier.
 *
 * La fonction vérifie notamment :
 * - la position des tirets ;
 * - la présence exclusive de chiffres ;
 * - les limites des mois et des jours ;
 * - les années bissextiles.
 */
bool BitcoinExchange::_isValidDate(const std::string &date) const
{
    if (date.size() != 10) // Format attendu : YYYY-MM-DD
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    for (std::string::size_type i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7) 
            continue;

        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    const int year = std::atoi(date.substr(0, 4).c_str());
    const int month = std::atoi(date.substr(5, 2).c_str());
    const int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false;

    static const int daysPerMonth[12] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    }; // Nombre de jours par mois, sans tenir compte des années bissextiles.

    int maximumDay = daysPerMonth[month - 1]; // Ajustement de l'indice du tableau (0-based)

	// Vérification des années bissextiles : un an est bissextile s'il est divisible par 4,
	// sauf s'il est divisible par 100, à moins qu'il ne soit divisible par 400.
    const bool leapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);

    if (month == 2 && leapYear) // Février d'une année bissextile
        maximumDay = 29;

    return day <= maximumDay;
}

/**
 * Verifie qu'une chaine represente un nombre valide et convertit ce nombre en double.
 *
 * La fonction accepte une partie decimale et une notation scientifique eventuelle.
 * Les limites imposées par le sujet sont vérifiees plus tard dans processInput().
 *
 * @param valueStr Représentation textuelle du nombre.
 * @param value Variable recevant la valeur convertie.
 * @return true si toute la chaîne représente un nombre valide.
 */
bool BitcoinExchange::_isValidValue(const std::string &valueStr, double &value) const
{
    if (valueStr.empty())
        return false;

    std::string::size_type pos = 0;

	// Verification du signe optionnel
    if (valueStr[pos] == '+' || valueStr[pos] == '-')
        ++pos;

    bool hasDigit = false;
	
	// Verification de la partie entiere
    while (pos < valueStr.size() 
		&& std::isdigit(static_cast<unsigned char>(valueStr[pos])))
    {
        hasDigit = true;
        ++pos;
    }

	// Verification de la partie décimale
    if (pos < valueStr.size() && valueStr[pos] == '.')
    {
        ++pos;
        while (pos < valueStr.size()
			&& std::isdigit(static_cast<unsigned char>(valueStr[pos])))
        {
            hasDigit = true;
            ++pos;
        }
    }

    if (!hasDigit)
        return false;

	// Verification de la notation scientifique optionnelle
    if (pos < valueStr.size() && (valueStr[pos] == 'e' || valueStr[pos] == 'E'))
    {
        ++pos;

        if (pos < valueStr.size() && (valueStr[pos] == '+' || valueStr[pos] == '-'))
            ++pos;

        bool hasExponentDigit = false;

        while (pos < valueStr.size() 
			&& std::isdigit(static_cast<unsigned char>(valueStr[pos])))
        {
            hasExponentDigit = true;
            ++pos;
        }

        if (!hasExponentDigit)
            return false;
    }

    if (pos != valueStr.size())
        return false;

	// Conversion de la chaîne en double une fois la syntaxe verifiee
	// end doit pointer sur la fin de la chaine : sinon une partie du texte n'a 
	// pas pu etre convertie
    char *end;
    const char *begin = valueStr.c_str();

    value = std::strtod(begin, &end);

    if (begin == end || *end != '\0')
        return false;

    // Une valeur NaN est la seule valeur differente d'elle-meme.
    if (value != value)
        return false;

    return true;
}

/**
 * Charge les taux contenus dans le fichier CSV.
 * Le fichier doit commencer par l'en-tête : date,exchange_rate
 *
 * La base est d'abord construite dans une map temporaire.
 * L'attribut _dB n'est remplace qu'une fois l'integralite du fichier valide.
 *
 * @return true si le chargement complet a reussi.
 */
bool BitcoinExchange::loadDatabase(const std::string &databasePath)
{
    std::ifstream file(databasePath.c_str());

    if (!file.is_open())
        return false;

    std::string line;

    if (!std::getline(file, line))
        return false;

    if (_trim(line) != "date,exchange_rate")
        return false;

	// Les donnees sont chargees dans une map temporaire pour ne pas modifier l'attribut _dB
    std::map<std::string, double> dB;

    while (std::getline(file, line))
    {
        const std::string trimmedLine = _trim(line);

        if (trimmedLine.empty())
            continue;

        const std::string::size_type comma = trimmedLine.find(',');

        if (comma == std::string::npos 
			|| trimmedLine.find(',', comma + 1) != std::string::npos)
            return false;

        const std::string date = _trim(trimmedLine.substr(0, comma));

        const std::string rateStr = _trim(trimmedLine.substr(comma + 1));

        double rate;

        if (!_isValidDate(date) || !_isValidValue(rateStr, rate) || rate < 0)
            return false;

        dB[date] = rate;
    }

    if (file.bad() || dB.empty())
        return false;

	// Toutes les lignes etant valides, la base temporaire devient la base definitive de l'objet
    _dB.swap(dB);
    return true;
}

/**
 * Lit le fichier fourni par l'utilisateur et traite chaque ligne.
 *
 * Pour chaque date valide :
 * - le taux exact est utilise s'il existe ;
 * - sinon, le taux de la date anterieure la plus proche est utilise.
 *
 * Une ligne invalide produit une erreur mais n'interrompt pas
 * le traitement des lignes suivantes.
 */
bool BitcoinExchange::processInput(const std::string &inputPath) const
{
    std::ifstream file(inputPath.c_str());

    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return false;
    }

	// Verification de l'en-tête du fichier
    std::string line;
    if (!std::getline(file, line) || _trim(line) != "date | value")
	{
		std::cout << "Error: invalid input file." << std::endl;
		return false;
	}

	// Indique si au moins une ligne de données non vide a été rencontrée.
	bool hasData = false;

	// Lecture et traitement de chaque ligne du fichier
    while (std::getline(file, line))
    {
        const std::string trimmedLine = _trim(line);

    	// Les lignes vides ne sont pas considérées comme des données.
        if (trimmedLine.empty())
            continue;

		hasData = true;

        const std::string::size_type pipe = trimmedLine.find('|');

        if (pipe == std::string::npos
			|| trimmedLine.find('|', pipe + 1)
			!= std::string::npos)
        {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        const std::string date = _trim(trimmedLine.substr(0, pipe));

        const std::string valueStr = _trim(trimmedLine.substr(pipe + 1));

        if (!_isValidDate(date))
        {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        double value;

        if (!_isValidValue(valueStr, value))
        {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        if (value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

		/*
 		 * lower_bound(date) renvoie à la date ou à la date antérieure la plus proche
 		 *
 		 * Trois cas sont possibles :
 		* - la clé correspond exactement : on utilise ce taux ;
	    * - la clé est supérieure ou end() : on recule d'une position ;
        * - l'itérateur vaut begin() sans correspondance exacte :
  		*   aucune date antérieure n'existe dans la base.
  		*/
        std::map<std::string, double>::const_iterator rate = _dB.lower_bound(date);

        if (rate == _dB.end() || rate->first != date)
        {
            if (rate == _dB.begin())
            {
                std::cout << "Error: no exchange rate available => " << date << std::endl;
                continue;
            }
            --rate;
        }

		// Affichage du résultat : date, valeur et taux correspondant
        std::cout << date << " => " << value << " = " << value * rate->second << std::endl;
    }
    
	// Vérifie d'abord qu'aucune erreur grave de lecture n'est survenue.
    if (file.bad())
    {
        std::cout << "Error: failed while reading input file." << std::endl;
        return false;
    }

    // Le fichier ne contenait que l'en-tête ou des lignes vides.
    if (!hasData)
    {
        std::cout << "Error: input file contains no data." << std::endl;
        return false;
    }
	return true;
}
