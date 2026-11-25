#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <map>
#include <string>

/**
 * Charge un historique des taux du Bitcoin depuis un fichier CSV,
 * puis evalue les valeurs contenues dans un second fichier.
 *
 * Les taux sont stockes dans une std::map :
 * - la cle represente une date au format YYYY-MM-DD ;
 * - la valeur represente le taux du Bitcoin associe a cette date.
 *
 * La std::map ne conserve pas l'ordre d'insertion du fichier :
 * elle maintient automatiquement ses cles triees.
 *
 * Le format ISO des dates permet a l'ordre lexicographique des cles
 * de correspondre a leur ordre chronologique. Cette organisation
 * permet notamment de rechercher efficacement la date inferieure
 * la plus proche avec lower_bound().
 */
class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		bool loadDatabase(const std::string &databasePath);
		bool processInput(const std::string &inputPath) const;

	private:
    	std::map<std::string, double> _dB;

    	std::string _trim(const std::string &str) const;
    	bool _isValidDate(const std::string &date) const;
    	bool _isValidValue(const std::string &valueString, double &value) const;
		void _processLine(const std::string &line) const;
};

#endif
