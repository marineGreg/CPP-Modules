#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <cstdlib>

class BitcoinExchange {
private:
    std::map<std::string, double> _database;

    bool        _isValidDate(const std::string& date) const;
    bool        _isValidValue(const std::string& valStr, double& value) const;
    std::string _trim(const std::string& str) const;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string& dbPath);
    void processInput(const std::string& inputPath) const;
};

#endif
