#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <limits>

class ScalarConverter{
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter &other);
        ~ScalarConverter();
        ScalarConverter& operator=(const ScalarConverter &other);
    public:
        static void convert(std::string str);
};

void convertChar(std::string &str);
void convertInt(std::string &str);
void convertFloat(std::string &str);
void convertDouble(std::string &str);