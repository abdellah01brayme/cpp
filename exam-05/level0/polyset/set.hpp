#include "searchable_bag.hpp"
#include <iostream>

class set
{
    private:
        searchable_bag &data;
        set();
        set(const searchable_bag &other);
        searchable_bag& operator=(const searchable_bag &);
    public:
        set(searchable_bag &data);
        ~set();
        searchable_bag& get_bag() const;
        void insert(int);
        void insert(int *array, int size);
        void print() const;
        void clear();
        bool has(int) const;
};
