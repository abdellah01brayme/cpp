#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}
ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    (void)other;
}
ScalarConverter::~ScalarConverter()
{
}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
{
    (void)other;
    return *this;
}

bool isChar(std::string &str)
{
    if (str.length() == 1 && !isdigit(str[0]))
        return true;
    return false;
}

bool isInt(std::string &str)
{
    int i = 0;
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (!isdigit(str[i]))
        return false;
    for ( ; str[i]; i++)
        if (!isdigit(str[i]))
            return false;
    return true;
}

bool isFloat(std::string &str)
{
    int i = 0;

    if (str == "-inff" || str == "+inff" || str == "nanf")
        return (true);
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (isdigit(str[i]))
        i++;
    if (str[i] == '.')
        i++;
    else
        return false;
    if (!isdigit(str[i]))
        return false;
    while (isdigit(str[i]))
        i++;
    if (str[i] == 'f' && !str[i + 1])
        return (true);
    return false;
}

bool isDouble(std::string &str)
{
    int i = 0;

    if (str == "-inf" || str == "+inf" || str == "nan")
        return (true);
    if (str[0] == '-' || str[0] == '+')
        i++;
    while (isdigit(str[i]))
        i++;
    if (str[i] == '.')
        i++;
    else
        return false;
    if (!isdigit(str[i]))
        return false;
    while (isdigit(str[i]))
        i++;
    if (!str[i])
        return (true);
    return false;
}

void ScalarConverter::convert(std::string str)
{
    if (str.empty())
        std::cerr<< "Error: empty input\n";
    else if (isChar(str))
        convertChar(str);
    else if (isInt(str))
        convertInt(str);
    else if (isFloat(str))
        convertFloat(str);
    else if (isDouble(str))
        convertDouble(str);
    else
        std::cerr<< "Error: invalide input\n";
}
