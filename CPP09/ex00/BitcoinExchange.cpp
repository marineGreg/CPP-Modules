#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        this->_database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// Trim nettoyant les espaces, tabulations ET retours à la ligne (\r, \n)
std::string BitcoinExchange::_trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::_isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (size_t i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    } else if (month == 2) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (isLeap ? 29 : 28))
            return false;
    }

    return true;
}

bool BitcoinExchange::_isValidValue(const std::string& valStr, double& value) const {
    if (valStr.empty())
        return false;

    char* endPtr;
    value = std::strtod(valStr.c_str(), &endPtr);

    if (*endPtr != '\0' && *endPtr != 'f')
        return false;

    return true;
}

bool BitcoinExchange::loadDatabase(const std::string& dbPath) {
    std::ifstream file(dbPath.c_str());
    if (!file.is_open())
        return false;

    std::string line;
    std::getline(file, line); // Sauter le header "date,exchange_rate"

    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string date = _trim(line.substr(0, commaPos));
            std::string rateStr = _trim(line.substr(commaPos + 1));
            double rate = std::atof(rateStr.c_str());
            _database[date] = rate;
        }
    }
    file.close();
    return true;
}

void BitcoinExchange::processInput(const std::string& inputPath) const {
    std::ifstream file(inputPath.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string trimmedLine = _trim(line);
        if (trimmedLine.empty() || trimmedLine == "date | value")
            continue;

        size_t pipePos = trimmedLine.find('|');
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        std::string date = _trim(trimmedLine.substr(0, pipePos));
        std::string valStr = _trim(trimmedLine.substr(pipePos + 1));

        if (!_isValidDate(date)) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        double value;
        if (!_isValidValue(valStr, value)) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        // Trouver la date égale ou la plus proche inférieure dans le map
        std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

        if (it == _database.end() || it->first != date) {
            if (it == _database.begin()) {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }
            --it;
        }

        double result = value * it->second;
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    file.close();
}
