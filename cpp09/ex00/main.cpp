#include "BitcoinExchange.hpp"

void print(std::map<std::string, double> &data)
{
    for (std::map<std::string, double>::iterator it = data.begin(); it != data.end(); ++it)
        std::cout <<  (*it).first << " => " << (*it).second << std::endl;
}

int main(int ac, char **av)
{
    std::map<std::string, double> data;
    try
    {
        if (ac != 2)
            throw std::runtime_error("too many arguments");
        readSrc(data, "input.csv");
        btc(data, av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " <<e.what() << '\n';
        return 1;
    }
    return 0;
}