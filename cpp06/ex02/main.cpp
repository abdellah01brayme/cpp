#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <stdexcept>
#include <typeinfo>
Base *generate(void)
{
    Base *ptr;

    int n = rand() % 3;
    if (!n)
    {
        // std::cout<<"Generate: A\n";
        ptr = new A;
    }
    else if (n == 1)
    {
        // std::cout<<"Generate: B\n";
        ptr = new B;
    }
    else
    {
        // std::cout<<"Generate: C\n";
        ptr = new C;
    }
    return ptr;
}

void identify(Base *ptr)
{
    if (dynamic_cast<A*>(ptr))
        std::cout << "Object type is: A\n";
    else if (dynamic_cast<B*>(ptr))
        std::cout << "Object type is: B\n";
    else if (dynamic_cast<C*>(ptr))
        std::cout << "Object type is: C\n";
}
void identify(Base& ptr)
{
    try
    {
        dynamic_cast<A&>(ptr);
        std::cout << "Object type is: A" << '\n';
        return ;
    }
    catch(const std::exception& e)
    {
    }

    try
    {
        dynamic_cast<B&>(ptr);
        std::cout << "Object type is: B" << '\n';
        return ;
    }
    catch(const std::exception& e)
    {
    }

    try
    {
        dynamic_cast<C&>(ptr);
        std::cout << "Object type is: C" << '\n';
        return ;
    }
    catch(const std::exception& e)
    {
    }
}
int main(void)
{
    srand(time(NULL));
    Base *base = generate();
    identify(*base);
    delete base;
    return 0;
}