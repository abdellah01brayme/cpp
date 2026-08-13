#include "BitcoinExchange.hpp"

static bool checkDate(std::string date)
{
//year
    int i = 0;
    int n;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 4 || n < 0 || date[i] != DELIMITER_DATE)
        return false;
    date.erase(0, 5);
//month
    i = 0;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 2 || n < 0 || n > 12 || date[i] != DELIMITER_DATE)
        return false;
    date.erase(0, 3);
//day
    i = 0;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 2 || n < 0 || n > 31 || date[i])
        return false;
    return true;
}

static bool checkValue(std::string value)
{
    int i = 0;
    if (value[i] == '-')
        i++;
    while (isdigit(value[i]))
        i++;
    if (value[i] == '.')
        i++;
    while (isdigit(value[i]))
        i++;
    if (value[i])
        return false;
    double f;
    std::stringstream ss(value.c_str());
    ss >> f;
    if (f < 0)
        throw std::runtime_error(std::string("not a positive number."));
    if (f > std::numeric_limits<int>::max())
        throw std::runtime_error(std::string("too large a number."));
    return true;
}

static void checkLine(std::string line)
{
    size_t start;
    std::string date, value;
    if (line.empty())
        throw std::runtime_error(std::string("empty line."));
    start = line.find(" | ");
    if (start == std::string::npos)
        throw std::runtime_error(std::string("bad input ==> ") + line);
    date = line.substr(0, start);
    value = line.substr(start + 3);  
    if (!checkDate(date) || !checkValue(value))
        throw std::runtime_error(std::string("bad input ==> ") + line);
}

void readSrc(std::map<std::string, double> &data, const std::string &file_name)
{
    std::ifstream file(file_name.c_str());
    std::string line;
    if (!file.is_open())
        throw std::runtime_error(std::string("opening file: ") + file_name);
    if (std::getline(file, line))
    {
        if (line != "date | value")
            throw std::runtime_error("Invalid header file!!!");
    }
    else if (!file.eof())
        throw std::runtime_error("reading file!!!");
    while (getline(file, line))
    {
        checkLine(line);
        std::string date = line.substr(0, 10);
        std::string value = line.substr(13);  
        float n;
        std::stringstream(value.c_str()) >> n;
        data[date] = n;
    }
    if (!file.eof())
        throw std::runtime_error("reading file!!!");
}

static double getPrice(std::map<std::string, double> &data, const std::string &date)
{
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if (it == data.end())
        --it;
    return (*it).second;
}

void btc(std::map<std::string, double> &data, const char *file_name)
{
    if (data.empty())
        throw std::runtime_error("No data to search from!!!");
    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::runtime_error(std::string("opening file: ") + file_name);
    std::string line;
    if (std::getline(file, line))
    {
        if (line != "date | value")
            throw std::runtime_error("Invalid header file!!!");
    }
    else if (!file.eof())
        throw std::runtime_error("Empty file!!!");
    while (getline(file, line))
    {
        try
        {
            checkLine(line);
            std::string date = line.substr(0, 10);
            std::string value = line.substr(13);
            double f;
            std::stringstream(value.c_str()) >> f;
            double result = f * getPrice(data, date);
            std::cout << date << " ==> " << value << " = " << result<< std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    if (!file.eof())
        throw std::runtime_error("reading file!!!");
}
