#pragma once
#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T &ref, int n)
{
    typename T:: iterator it = std::find(ref.begin(), ref.end(), n);
    if (it == ref.end())
        throw std::runtime_error("value not found!");
    return it;
}