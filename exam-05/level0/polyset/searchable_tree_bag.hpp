#include "tree_bag.hpp"
#include "searchable_bag.hpp"
class searchable_tree_bag : public tree_bag, public searchable_bag
{
    private:
        bool search(tree_bag:: node *tree, int item) const;
    public:
        searchable_tree_bag();
        searchable_tree_bag(const searchable_tree_bag &other);
        searchable_tree_bag &operator=(const searchable_tree_bag &other);
        ~searchable_tree_bag();
        virtual void insert(int);
        virtual void insert(int *array, int size);
        virtual void print() const;
        virtual void clear();
        virtual bool has(int) const;
};