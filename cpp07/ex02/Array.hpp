#pragma once
#include <stdexcept>
#include <iostream>

template <typename T>
class Array{
    private:
        T *arr;
        unsigned int lenght;
    public:
        Array();
        Array(unsigned int n);
        Array(const Array &other);
        ~Array();
        Array &operator=(const Array &other);
        T &operator[](unsigned int i);
        unsigned int size() const;
};

#include "Array.tpp"
