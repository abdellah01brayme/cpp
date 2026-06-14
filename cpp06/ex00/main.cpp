#include "ScalarConverter.hpp"

int main(int ac, char **av) {
    if (ac != 2)
    {
        std::cerr<<"Error: the number of agrs\n";
        return (1);
    }
    ScalarConverter::convert(av[1]);
    return 0;
}