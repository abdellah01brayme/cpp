#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag(): tree_bag()
{
}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &other):tree_bag(other)
{

}
searchable_tree_bag &searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
    tree_bag::operator=(other);
    return *this;
}
searchable_tree_bag::~searchable_tree_bag()
{
}
void searchable_tree_bag::insert(int item)
{
    tree_bag::insert(item);
}
void searchable_tree_bag::insert(int *array, int size)
{
    tree_bag::insert(array, size);
}
void searchable_tree_bag::print() const
{
    tree_bag::print();
}
void searchable_tree_bag::clear()
{
    tree_bag::clear();
}

bool searchable_tree_bag::search(tree_bag:: node *tree, int item) const
{
    if (!tree)
        return false;
    if (tree->value)
        return true;
    return (search(tree->l, item) || search(tree->r, item));
}

bool searchable_tree_bag::has(int item) const
{
    return search(tree, item);
}