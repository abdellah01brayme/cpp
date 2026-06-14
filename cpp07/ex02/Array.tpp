#include "Array.hpp"

template <typename T>
Array<T>::Array(): arr(0), lenght(0){};

template <typename T>
Array<T>::Array(unsigned int n): lenght(n)
{
    arr = new T[lenght]();
}

template <typename T>
Array<T>::Array(const Array &other)
{
    lenght = other.lenght;
    arr = new T[other.lenght];
    for (unsigned int i = 0; i < lenght; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array &other)
{
    delete arr;
    lenght = other.lenght;
    arr = new T[other.lenght];
    for (unsigned int i = 0; i < lenght; i++)
    {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Array<T>::~Array()
{
    delete[] arr;
}

template <typename T>
T& Array<T>::operator[](unsigned int i)
{
    if (i >= lenght)
        throw std::out_of_range("Index out of bounds");
    return arr[i];
}
template <typename T>
unsigned int Array<T>::size() const
{
    return lenght;
}
