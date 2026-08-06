#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

class Span
{
    private:
        unsigned int N;
        std::vector<int> v;
        Span();
    public:
        Span(unsigned int N);
        Span(const Span &other);
        ~Span();
        Span &operator=(const Span &other);
        void addNumber(int n);
        template <typename Iterator>
        void addRange(Iterator begin, Iterator end);
        int shortestSpan();
        int longestSpan();
};


template <typename Iterator>
void Span::addRange(Iterator begin, Iterator end)
{
    long count = std::distance(begin, end);
    if (count < 0)
        throw std::runtime_error("invalide iterator range!");
    else if (v.size() + count > N)
        throw std::runtime_error("no enough space on Span!");
    v.insert(v.end(), begin, end);
}