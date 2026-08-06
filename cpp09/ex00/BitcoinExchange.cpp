#include "BitcoinExchange.hpp"


static bool checkDate(std::string date)
{
//year
    int i = 0;
    int n;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 4 || n < 0)
        return false;
    if (date[i] != '-')
        return false;
    date.erase(0, 5);
//month
    i = 0;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 2 || n < 0 || n > 12)
        return false;
    if (date[i] != '-')
        return false;
    date.erase(0, 3);
//day
    i = 0;
    while (isdigit(date[i]))
        i++;
    std::stringstream(date.c_str()) >> n;
    if (i != 2 || n < 0 || n > 31)
        return false;
    if (date[i])
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
    std::stringstream ss(value.c_str()) ;
    ss >> f;
    if (f < 0)
        throw std::runtime_error(std::string("not a positive number."));
    if (f > std::numeric_limits<int>::max())
        throw std::runtime_error(std::string("too large a number."));
    return true;
}

void BitcoinExchange::checkLine(std::string line)
{
    size_t start;
    std::string date, value;
    start = line.find(" | ");
    if (start == std::string::npos)
        throw std::runtime_error(std::string("bad input ==> ") + line);
    date = line.substr(0, start);
    value = line.substr(start + 3);  
    if (!checkDate(date) || !checkValue(value))
        throw std::runtime_error(std::string("bad input ==> ") + line);
}

BitcoinExchange::BitcoinExchange(const std::string &fileName)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(fileName.c_str());
        std::string line;
        if (std::getline(file, line))
        {
            if (line != "date | value")
                throw std::runtime_error("Invalid header file!!!");
        }
        else
            throw std::runtime_error("Empty file!!!");
        while (getline(file, line))
        {
            checkLine(line);
            std::string date = line.substr(0, 10);
            std::string value = line.substr(13);  
            float n;
            std::stringstream(value.c_str()) >> n;
            data[date] = n;
        }
    }
    catch(const std::ios_base::failure& e)
    {
        if (!file.eof())
            std::cerr << e.what() << '\n';
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other):data(other.data)
{

}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        this->data = other.data;
    }
    return *this;
}

double BitcoinExchange::getPrice(const std::string date) const
{
    std::map<std::string, double>::const_iterator it = data.begin();
    if (date < (*it).first)
        throw std::runtime_error("date to old!");
    if ((*it).first >= date)
        return (*(--it)).second;
    for ( ; it != data.end(); ++it)
    {
        return (*(--it)).second;
        
    }
    return (*(--it)).second;
}