# include "Array.hpp"
# include <iostream>

int main( void )
{
    Array<int> arr(6);
    arr[0] = 11;
    arr[1] = 22;
    arr[2] = 33;
    arr[3] = 44;
    arr[4] = 55;
    std::cout << "size: " << arr.size() << std:: endl;
    try
    {
        std::cout << arr[0] << std::endl;
        std::cout << arr[12];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return (0);
}