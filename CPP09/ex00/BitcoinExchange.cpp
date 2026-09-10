#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
    : _database(src._database) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::_trim(const std::string &str) const
{
    const std::string whitespace = " \t\r\n";

    std::string::size_type start = str.find_first_not_of(whitespace);

    if (start == std::string::npos)
        return "";

    std::string::size_type end = str.find_last_not_of(whitespace);

    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::_isValidDate(const std::string &date) const
{
    if (date.size() != 10)
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
    };

    int maximumDay = daysPerMonth[month - 1];

    const bool leapYear = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);

    if (month == 2 && leapYear)
        maximumDay = 29;

    return day <= maximumDay;
}

bool BitcoinExchange::_isValidValue(const std::string &valueString, double &value) const
{
    if (valueString.empty())
        return false;

    std::string::size_type position = 0;

    if (valueString[position] == '+' || valueString[position] == '-')
        ++position;

    bool hasDigit = false;

    while (position < valueString.size() && std::isdigit(static_cast<unsigned char>(valueString[position])))
    {
        hasDigit = true;
        ++position;
    }

    if (position < valueString.size() && valueString[position] == '.')
    {
        ++position;
        while (position < valueString.size() && std::isdigit(static_cast<unsigned char>(valueString[position])))
        {
            hasDigit = true;
            ++position;
        }
    }

    if (!hasDigit)
        return false;

    if (position < valueString.size() && (valueString[position] == 'e' || valueString[position] == 'E'))
    {
        ++position;

        if (position < valueString.size() && (valueString[position] == '+' || valueString[position] == '-'))
            ++position;

        bool hasExponentDigit = false;

        while (position < valueString.size() && std::isdigit(static_cast<unsigned char>(valueString[position])))
        {
            hasExponentDigit = true;
            ++position;
        }

        if (!hasExponentDigit)
            return false;
    }

    if (position != valueString.size())
        return false;

    char *end;
    const char *begin = valueString.c_str();

    value = std::strtod(begin, &end);

    if (begin == end || *end != '\0')
        return false;

    // Une valeur NaN est la seule valeur différente d'elle-même.
    if (value != value)
        return false;

    return true;
}

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

    std::map<std::string, double> database;

    while (std::getline(file, line))
    {
        const std::string trimmedLine = _trim(line);

        if (trimmedLine.empty())
            continue;

        const std::string::size_type comma = trimmedLine.find(',');

        if (comma == std::string::npos || trimmedLine.find(',', comma + 1) != std::string::npos)
            return false;

        const std::string date = _trim(trimmedLine.substr(0, comma));

        const std::string rateString = _trim(trimmedLine.substr(comma + 1));

        double rate;

        if (!_isValidDate(date) || !_isValidValue(rateString, rate) || rate < 0)
            return false;

        database[date] = rate;
    }

    if (file.bad() || database.empty())
        return false;

    _database.swap(database);
    return true;
}

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
		std::cout << "Error: ivalid input file." << std::endl;
		return false;
	}

    while (std::getline(file, line))
    {
        const std::string trimmedLine = _trim(line);

        if (trimmedLine.empty())
            continue;

        const std::string::size_type pipe = trimmedLine.find('|');

        if (pipe == std::string::npos || trimmedLine.find('|', pipe + 1) != std::string::npos)
        {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        const std::string date = _trim(trimmedLine.substr(0, pipe));

        const std::string valueString = _trim(trimmedLine.substr(pipe + 1));

        if (!_isValidDate(date))
        {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        double value;

        if (!_isValidValue(valueString, value))
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

        std::map<std::string, double>::const_iterator rate = _database.lower_bound(date);

        if (rate == _database.end() || rate->first != date)
        {
            if (rate == _database.begin())
            {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }
            --rate;
        }

        std::cout << date << " => " << value << " = " << value * rate->second << std::endl;
    }
    return !file.bad();
}
