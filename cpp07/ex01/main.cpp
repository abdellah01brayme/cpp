#include "iter.hpp"

void mult11(int &n)
{
    n *= 11;
}

int main( void ) {
    int arrInt[9] = {1,2,3,4,5,6,7,8,9};
    iter(arrInt, 9, mult11);
    iter(arrInt, 9, print<int>);

    const std::string arrString[4] = {"word1", "word2", "word3", "word4"};
    iter(arrString, 4, print<const std::string>);
    return 0;
}