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
        void convertChar(std::string &str);
        void convertInt(std::string &str);
        void convertFloat(std::string &str);
        void convertDouble(std::string &str);
        void print(char c, int n, float f, double d);
        bool isDouble(std::string &str);
        bool isFloat(std::string &str);
        bool isInt(std::string &str);
        bool isChar(std::string &str);
    public:
        static void convert(std::string str);
};
