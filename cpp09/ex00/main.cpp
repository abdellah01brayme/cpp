#include "BitcoinExchange.hpp"


int main(int ac, char **av)
{
    (void)ac;
    try
    {
        BitcoinExchange input("input.csv");
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            file.open(av[1]);
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
                try
                {
                    BitcoinExchange::checkLine(line);
                    std::string date = line.substr(0, 10);
                    std::string value = line.substr(13);
                    double f;
                    std::stringstream(value.c_str()) >> f;
                    double result = f * input.getPrice(date);
                    std::cout << date << " ==> " << value << " = " << result<< std::endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error: " << e.what() << '\n';
                }
            }
        }
        catch(const std::ios_base::failure& e)
        {
            if (!file.eof())
                std::cerr << e.what() << '\n';
        }
    }
    catch(const std::exception& e)
    {
        std::cerr <<  "Error: " <<e.what() << '\n';
    }
    
   
    return 0;
}