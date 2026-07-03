#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter & src) { (void)src; }

ScalarConverter &ScalarConverter::operator=(const ScalarConverter & other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string & input) {

}
