#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    if (!btc.loadDatabase("data.csv")) {
        std::cout << "Error: could not load database file (data.csv)." << std::endl;
        return 1;
    }

    if (!btc.processInput(av[1]))
        return 1;

    return 0;
}
