#include <iostream>
#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "too many args\n";
        return 1;
    }
    try
    {
        RPN rpn(av[ac - 1]);
        std:: cout << "result: " << rpn.getResult() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    try
    {
        int n = RPN::calcul(av[ac - 1]);
        std:: cout << "result: " << n << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
