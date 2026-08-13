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

bool ScalarConverter::isChar(std::string &str)
{
    if (str.length() == 1 && !isdigit(str[0]))
        return true;
    return false;
}

bool ScalarConverter::isInt(std::string &str)
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

bool ScalarConverter::isFloat(std::string &str)
{
    int i = 0;

    if (str == "-inff" || str == "+inff" || str == "nanf")
        return (true);
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (!isdigit(str[i]))
        return false;
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

bool ScalarConverter::isDouble(std::string &str)
{
    int i = 0;

    if (str == "-inf" || str == "+inf" || str == "nan")
        return (true);
    if (str[0] == '-' || str[0] == '+')
        i++;
    if (!isdigit(str[i]))
        return false;
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

void ScalarConverter::print(char c, int n, float f, double d)
{
    /// char
    std::cout << "char: ";
    if (std::isnan(f) || std::isinf(f) || n < 0 || n > 127)
        std::cout <<"impossible\n";
    else if (std::isprint(c))
        std::cout << "'" << c << "'" << "\n";
    else
        std::cout << "Non displayable\n";
    // int
    std::cout << "int: ";
    if (std::isnan(f) || std::isinf(f)
        || f > std::numeric_limits<int>::max() || f < std::numeric_limits<int>::min())
        std::cout <<"impossible\n";
    else
        std::cout<< n << "\n";
    // float and double
    std::cout << std::fixed << std::setprecision(2);
    if (std::isinf(f))
        std::cout << "float: "<< (f > 0 ? "+inff" : "-inff") << "\n";
    else if (std::isnan(f))
        std::cout << "float: "<< "nanf" << "\n";
    std::cout << "double: "<< d << "\n";
}
void ScalarConverter::convertChar(std::string &str)
{
    char    c = str[0];
    int     n;
    float   f;
    double  d;

    n = static_cast<int>(c);
    f = static_cast<float>(c);
    d = static_cast<double>(c);
    print(c, n, f, d);
}
void ScalarConverter::convertInt(std::string &str)
{
    std::stringstream ss(str);
    char    c;
    float   f;
    double  d;
    long    l;
    ss >> l;

    if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min())
    {
        std:: cout << "char: impossible\n";
        std:: cout << "int: impossible\n";
        std:: cout << "float: impossible\n";
        std:: cout << "double: impossible\n";
    }
    else
    {
        c = static_cast<char>(l);
        f = static_cast<float>(l);
        d = static_cast<double>(l);
        int n = static_cast<int>(l);
        print(c, n, f, d);
    }
}
void ScalarConverter::convertFloat(std::string &str)
{
    std::stringstream ss(str);
    char    c;
    int     n;
    float   f;
    double  d;

    if (str == "nanf")
        f = std::numeric_limits<float>::quiet_NaN();
    else if (str == "+inff")
        f = std::numeric_limits<float>::infinity();
    else if (str == "-inff")
        f = -std::numeric_limits<float>::infinity();
    else
        ss >> f;
    c = static_cast<char>(f);
    n = static_cast<int>(f);
    d = static_cast<double>(f);
    print(c, n, f, d);
}
void ScalarConverter::convertDouble(std::string &str)
{
    std::stringstream ss(str);
    char    c;
    int     n;
    float   f;
    double  d;

    if (str == "nan")
        d = std::numeric_limits<double>::quiet_NaN();
    else if (str == "+inf")
        d = std::numeric_limits<double>::infinity();
    else if (str == "-inf")
        d = -std::numeric_limits<double>::infinity();
    else
        ss >> d;
    c = static_cast<char>(d);
    f = static_cast<float>(d);
    n = static_cast<int>(d);
    print(c, n, f, d);
}
void ScalarConverter::convert(std::string str)
{
    ScalarConverter s;
    if (str.empty())
        std::cerr<< "Error: empty input\n";
    else if (s.isChar(str))
        s.convertChar(str);
    else if (s.isInt(str))
        s.convertInt(str);
    else if (s.isFloat(str))
        s.convertFloat(str);
    else if (s.isDouble(str))
        s.convertDouble(str);
    else
        std::cerr<< "Error: invalide input\n";
}
