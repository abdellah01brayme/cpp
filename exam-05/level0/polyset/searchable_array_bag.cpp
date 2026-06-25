#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag():array_bag()
{
}
searchable_array_bag::searchable_array_bag(const searchable_array_bag &other):array_bag(other)
{
}
searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &other)
{
    array_bag::operator=(other);
    return *this;
}
searchable_array_bag::~searchable_array_bag()
{
}
void searchable_array_bag::insert(int item)
{
    array_bag::insert(item);
}
void searchable_array_bag::insert(int *items, int count)
{
    array_bag::insert(items, count);
}
void searchable_array_bag::print() const
{
    array_bag::print();
}
void searchable_array_bag::clear()
{
    array_bag::clear();
}

bool searchable_array_bag::has(int item) const
{
    for (int i = 0; i < size; i++)
    {
        if(data[i] == item)
            return true;
    }
    return false;
}