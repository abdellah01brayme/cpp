#pragma once
#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<int> >
class MutantStack: public std::stack<T, Container>
{
    public:
        MutantStack();
        MutantStack(const MutantStack& other);
        ~MutantStack();
        MutantStack& operator=(const MutantStack& other);
        typedef typename std::stack<T, Container>::container_type::iterator iterator;
        typedef typename std::stack<T, Container>::container_type::const_iterator const_iterator;
        iterator begin();
        iterator end();
    
        const_iterator begin() const;
        const_iterator end() const;
};

#include "MutantStack.tpp"