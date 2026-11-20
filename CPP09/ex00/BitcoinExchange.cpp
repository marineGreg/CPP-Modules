#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _dB(src._dB) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _dB = other._dB;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/**
 * Supprime les espaces et caracteres blancs situes au debut et a la fin d'une chaine.
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
 * Verifie qu'une date respecte le format YYYY-MM-DD
 * et qu'elle existe réellement dans le calendrier.
 *
 * La fonction verifie notamment :
 * - la position des tirets ;
 * - la presence exclusive de chiffres ;
 * - les limites des mois et des jours ;
 * - les annees bissextiles.
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
        31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
    };
	// Ajustement de l'indice du tableau (0-based)
    int maximumDay = daysPerMonth[month - 1];

	// Verification des annees bissextiles : un an est bissextile s'il est divisible 
	// par 4, sauf s'il est divisible par 100, a moins qu'il ne soit divisible par 400.
    const bool leapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);

    if (month == 2 && leapYear) // Fevrier d'une annee bissextile
        maximumDay = 29;

    return day <= maximumDay;
}

/**
 * Verifie qu'une chaine represente un nombre valide et convertit ce nombre en double.
 *
 * La fonction accepte une partie decimale et une notation scientifique eventuelle.
 * Les limites imposees par le sujet sont vérifiees plus tard dans processInput().
 *
 * @param valueStr Representation textuelle du nombre.
 * @param value Variable recevant la valeur convertie.
 * @return true si toute la chaine représente un nombre valide.
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

	// Verification de la partie decimale
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

	// toute la chaine doit etre consomme pour que la valeur soit valide.
    if (pos != valueStr.size())
        return false;

	/* La syntaxe a ete verifiee. Conversion de la chaine en double.
	 * begin pointe sur le debut de la chaine
	 * end pointe sur le premiere caractere non converti (ou fin de chaine)
	 */
    char *end;
    const char *begin = valueStr.c_str();

    value = std::strtod(begin, &end);

    if (begin == end || *end != '\0')
        return false;

	// NaN (not a number) n'est egal à aucune valeur, pas meme a lui-meme
    if (value != value)
        return false;

    return true;
}

/**
 * Charge les taux contenus dans le fichier CSV.
 * Le fichier doit commencer par l'en-tete : date,exchange_rate
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

		// Recherche de la virgule unique separant la date du taux.
        const std::string::size_type comma = trimmedLine.find(',');

        if (comma == std::string::npos 
			|| trimmedLine.find(',', comma + 1) != std::string::npos)
            return false;

        const std::string date = _trim(trimmedLine.substr(0, comma));

        const std::string rateStr = _trim(trimmedLine.substr(comma + 1));

        double rate;

        if (!_isValidDate(date) || !_isValidValue(rateStr, rate) || rate < 0)
            return false;

		// La date devient la cle et le taux devient la valeur.
        dB[date] = rate;
    }

    if (file.bad() || dB.empty())
        return false;

	// Lignes valides : la map temporaire devient la base definitive de l'objet
    _dB.swap(dB);
    return true;
}

/**
 * Traite une ligne non vide du fichier utilisateur.
 *
 * La fonction separe la date et la valeur, valide les deux champs,
 * recherche le taux correspondant puis affiche le resultat.
 *
 * Une ligne invalide affiche une erreur puis retourne simplement
 * a processInput(), qui pourra continuer avec la ligne suivante.
 */
void BitcoinExchange::_processLine(const std::string &line) const
{
    // Recherche l'unique separateur entre la date et la valeur
    const std::string::size_type pipe = line.find('|');

    if (pipe == std::string::npos
        || line.find('|', pipe + 1) != std::string::npos)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    const std::string date = _trim(line.substr(0, pipe));
    const std::string valueStr = _trim(line.substr(pipe + 1));

    if (!_isValidDate(date))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    double value;
    if (!_isValidValue(valueStr, value))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    if (value < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return;
    }

    if (value > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return;
    }

    // lower_bound() renvoie la 1ere date superieure ou egale a la date recherchee
    std::map<std::string, double>::const_iterator entry = _dB.lower_bound(date);

    // Si aucune correspondance exacte, selectionne la date anterieure la plus proche
    if (entry == _dB.end() || entry->first != date)
    {
        // Si entry vaut deja begin(), aucune date anterieure n'est disponible
        if (entry == _dB.begin())
        {
            std::cout << "Error: no exchange rate available => "
                	  << date << std::endl;
            return;
        }
        --entry; // Selectionne la date inferieure la plus proche
    }

    // Affichage du résultat : date, valeur et taux correspondant
    std::cout << date << " => " << value
        	  << " = " << value * entry->second
              << std::endl;
}

/**
 * Lit et traite le fichier d'entree fourni par l'utilisateur.
 *
 * Le fichier doit commencer par l'en-tete "date | value".
 * Les lignes vides sont ignorees et chaque ligne non vide est transmise
 * a _processLine(), qui verifie son contenu et affiche soit le resultat
 * de la conversion, soit l'erreur correspondante.
 *
 * Une ligne incorrecte n'interrompt pas la lecture : le reste du fichier
 * est toujours traite.
 */
bool BitcoinExchange::processInput(const std::string &inputPath) const
{
    std::ifstream file(inputPath.c_str());

    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(file, line) || _trim(line) != "date | value")
	{
		std::cout << "Error: invalid input file." << std::endl;
		return false;
	}

	bool hasData = false;

    while (std::getline(file, line))
    {
        const std::string trimmedLine = _trim(line);

        if (trimmedLine.empty())
            continue;

		hasData = true;
		_processLine(trimmedLine);
    }
    
	/*
     * La boucle peut se terminer normalement parce que getline()
     * a rencontre la fin du fichier. file.bad() distingue cette fin
     * normale d'une veritable erreur de lecture.
     */
    if (file.bad())
    {
        std::cout << "Error: failed while reading input file." << std::endl;
        return false;
    }

    if (!hasData)
    {
        std::cout << "Error: input file contains no data." << std::endl;
        return false;
    }
	return true;
}
