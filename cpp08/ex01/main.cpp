#include <iostream>
#include "Span.hpp"
#include <vector>
#include <list>
#include <ctime>

int main()
{

    std::cout << "\033[33m" << "42 test\n"<< "\033[0m";
    Span sp = Span(5);
    sp.addNumber(6);
    try
    {
        std::cout << sp.shortestSpan() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    try
    {
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
        s.addNumber(12);
        try
        {
            s.addRange(v.begin(), v.end());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        try
        {
            s.addRange(v.begin(), v.end() - 1);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << s.shortestSpan() << std::endl;
        std::cout << s.longestSpan() << std::endl;
    }
    

    std::cout << "\033[33m" << "\ntest with list\n"<< "\033[0m";
    {
        srand(time(NULL));
        Span s(1000);
        std::list<int> l(999);
        for (std::list <int>:: iterator it = l.begin(); it != l.end(); it++)
            *it = rand() % 999;
        s.addNumber(12);
        try
        {
            s.addRange(l.begin(), l.end());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        std::cout << s.shortestSpan() << std::endl;
        std::cout << s.longestSpan() << std::endl;
    }



    Span s(10000);
    srand(time(NULL));
    for(int i =0; i < 10000; i++)
        s.addNumber(rand() % 100000);
    std::cout << "shortestSpan = " << s.shortestSpan() << std::endl;
    std::cout << "longestSpan =  " << s.longestSpan() << std::endl;
    return 0;
}
