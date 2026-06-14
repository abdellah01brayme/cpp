#pragma once
#include <iostream>
#include <string>

template <typename T, typename Fun>
void iter(T *array, const int length, Fun f)
{
    for (int i = 0; i < length; i++)
        f(array[i]);
}


template <typename t>
void print(const t &n)
{
    std::cout << n << std::endl;
}
