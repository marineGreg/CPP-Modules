#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <string>

class BitcoinExchange
{
	private:
    	std::map<std::string, double> _database;

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
