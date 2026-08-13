#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: too many args\n";
        return 1;
    }
    try
    {
        int result = RPN(av[1]);
        std:: cout << "result: " << result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}
