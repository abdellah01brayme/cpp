#include "set.hpp"

set::set(searchable_bag &data):data(data)
{

}
set::~set()
{
}
searchable_bag& set::get_bag() const
{
    return (data);
}
void set::insert(int item)
{
    data.insert(item);
}
void set::insert(int *array, int size)
{
    data.insert(array, size);
}
void set::print() const
{
    data.print();
}
void set::clear()
{
    data.clear();
}
bool set::has(int item) const
{
    return (data.has(item));
}