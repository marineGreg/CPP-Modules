#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

/**
 * Charge un historique des taux du Bitcoin depuis un fichier CSV,
 * puis évalue les valeurs contenues dans un second fichier.
 *
 * Les taux sont stockes dans une std::map :
 * - la cle represente une date au format YYYY-MM-DD ;
 * - la valeur represente le taux associe à cette date.
 *
 * Le format ISO des dates permet de les comparer directement dans 
 * l'ordre chronologique avec l'ordre lexicographique.
 */
class BitcoinExchange
{
	private:
    	std::map<std::string, double> _dB; // Map cle = valeur contenant les taux du Bitcoin par date

    	std::string _trim(const std::string &str) const;
    	bool _isValidDate(const std::string &date) const;
    	bool _isValidValue(const std::string &valueString, double &value) const;

	public:
    	BitcoinExchange();
    	BitcoinExchange(const BitcoinExchange &src);
    	BitcoinExchange &operator=(const BitcoinExchange &other);
    	~BitcoinExchange();

    	bool loadDatabase(const std::string &databasePath);
    	bool processInput(const std::string &inputPath) const;
};

#endif
