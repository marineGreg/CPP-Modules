#include "iter.hpp"
#include <iostream>
#include <string>
#include <cctype>

template <typename T>
void print(T const & item) {
	std::cout << item << " ";
}	

template <typename T>
void decrement(T & item) {
    item--;
}

void toUpper(std::string &str) {
	for (size_t i = 0; i < str.length(); i++) {
		str[i] = std::toupper(str[i]);
	}
}

int main() {
    std::cout << "===== Test Integers =====" << std::endl;
    int tabInt[] = {9, 8, 7, 6, 5};
    std::cout << "Avant decrement : ";
    iter(tabInt, 5, print<int>);
    std::cout << std::endl;
    iter(tabInt, 5, decrement<int>);
    std::cout << "Apres decrement : ";
    iter(tabInt, 5, print<int>);
    std::cout << std::endl;

	std::cout << "\n===== Test Characters =====" << std::endl;
	char tabChar[] = {'v', 'w', 'x', 'y', 'z'};
	std::cout << "Avant decrement : ";
	iter(tabChar, 5, print<char>);
	std::cout << std::endl;
	iter(tabChar, 5, decrement<char>);
	std::cout << "Apres decrement : ";
	iter(tabChar, 5, print<char>);
	std::cout << std::endl;

	std::cout << "\n===== Test Doubles =====" << std::endl;
	double tabDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	std::cout << "Avant decrement : ";
	iter(tabDouble, 5, print<double>);
	std::cout << std::endl;
	iter(tabDouble, 5, decrement<double>);
	std::cout << "Apres decrement : ";
	iter(tabDouble, 5, print<double>);
	std::cout << std::endl;

    std::cout << "\n===== Test Strings =====" << std::endl;
    std::string tabStr[] = {"hello", "world", "holy", "graph", "cursus"};
    std::cout << "Avant toUpper : ";
    iter(tabStr, 5, print<std::string>);
    std::cout << std::endl;
    iter(tabStr, 5, toUpper);
    std::cout << "Apres toUpper : ";
    iter(tabStr, 5, print<std::string>);
    std::cout << std::endl;

    std::cout << "\n===== Test Constants =====" << std::endl;
    const int tabConst[] = {10, 20, 30, 40, 50};
    std::cout << "Lecture de tableau constant : ";
    iter(tabConst, 5, print<const int>);
    std::cout << std::endl;

    return 0;
}
