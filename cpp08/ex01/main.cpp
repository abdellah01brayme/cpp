#include "Span.hpp"
#include <iostream>
#include <list>
#include <ctime>

int main()
{

    std::cout << "\033[33m" << "42 test\n"<< "\033[0m";
    Span sp = Span(5);
    try
    {
        sp.addNumber(6);
        std::cout << sp.shortestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
        sp.addNumber(11);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\033[33m" << "\ntest with vector and more than 10000 numbers\n"<< "\033[0m";
    {
        srand(time(NULL));
        Span s(15000);
        std::vector<int> v(15000);
        for (std::vector <int>:: iterator it = v.begin(); it != v.end(); it++)
            *it = rand() % 15000;
        try
        {
            s.addNumber(12);
            s.addRange(v.begin(), v.end());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            try
            {
                s.addRange(v.begin(), v.end() - 1);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return 1;
            }
        }
        std::cout << s.shortestSpan() << std::endl;
        std::cout << s.longestSpan() << std::endl;
    }
    

    std::cout << "\033[33m" << "\ntest with list\n"<< "\033[0m";
    {
        Span s(1000);
        s.addNumber(12);
        try
        {
            std::cout << s.shortestSpan() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        try
        {
            s.addNumber(1);
            std::cout << s.longestSpan() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return 0;
}
