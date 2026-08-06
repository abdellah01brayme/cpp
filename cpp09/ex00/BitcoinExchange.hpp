#pragma once
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <algorithm>
#include <iostream>
#include <limits>

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;
        BitcoinExchange();
        public:
        BitcoinExchange(const std::string &fileName);
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();
        BitcoinExchange& operator=(const BitcoinExchange &other);
        double getPrice(const std::string date) const;
        
        static void checkLine(std::string line);

        void print()
        {
            for (std::map<std::string, double>::iterator it = data.begin(); it != data.end(); ++it)
                std::cout <<  (*it).first << " => " << (*it).second << std::endl;
        }
};



