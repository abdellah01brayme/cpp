#include "Serializer.hpp"
#include <iostream>

int main(void)
{
    Data data;
    data.name = "Abdellah";
    data.age = 25;
    std::cout<< "data: " << data.name << " " << data.age << " years.\n";
    uintptr_t ptr = Serializer::serialize(&data);
    Data *p = Serializer::deserialize(ptr);
    std:: cout <<"data: "<< p->name << " " << p->age<< " years\n";
    if (p == &data)
        std::cout << "pointers match: OK\n";
    else
        std::cout << "pointers do not match: FAIL\n";
    return 0;
}