#include "ScalarConverter.hpp"

static void print(char c, int n, float f, double d)
{
    /// char
    std::cout << "char: ";
    if (std::isnan(f) || std::isinf(f) || n < 0 || n > 127)
        std::cout <<"impossible\n";
    else if (std::isprint(c))
        std::cout << "'" << c << "'" << "\n";
    else if ((c >= 0 && c < 32) || c == 127)
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
    std::cout << "float: "<< (f > 0 ? "+inff" : "-inff") << "\n";
    std::cout << "double: "<< (d > 0 ? "+inf" : "-inf") << "\n";
}
void convertChar(std::string &str)
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
void convertInt(std::string &str)
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
void convertFloat(std::string &str)
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
void convertDouble(std::string &str)
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