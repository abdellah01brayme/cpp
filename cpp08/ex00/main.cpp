#include <iostream>
#include "easyfind.hpp"
#include <vector>
#include <deque>
#include <list>

int main()
{
    std::cout << "\033[33m" << "Test vector container\n"<< "\033[0m";
    std:: vector <int> v;
    for (int i = 1; i < 5; i++)
        v.push_back(i * 10);
    try
    {
        std::cout << "find: " << *easyfind(v, 30) << "\n";
        std::cout << "find: " << *easyfind(v, 50) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << "\033[33m" << "Test deque container\n"<< "\033[0m";
    std:: deque <int> d;
    for (int i = 1; i < 5; i++)
        d.push_back(i * 10);
    try
    {
        std::cout << "find: " << *easyfind(d, 30) << "\n";
        std::cout << "find: " << *easyfind(d, 50) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "\033[33m" << "Test list container\n"<< "\033[0m";
    std:: list<int> l;
    for (int i = 1; i < 5; i++)
        l.push_back(i * 10);
    try
    {
        std::cout << "find: " << *easyfind(l, 30) << "\n";
        std::cout << "find: " << *easyfind(l, 50) << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}