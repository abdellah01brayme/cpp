#include "Span.hpp"

Span::Span(unsigned int N): N(N)
{
    v.reserve(N);
}

Span::~Span()
{
}

Span::Span(const Span &other): N(other.N), v(other.v)
{

}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        this->N = other.N;
        this->v = other.v;
    }
    return *this;
}
void Span::addNumber(int n)
{
    if (v.size() == N)
        throw std::runtime_error("no enough space in Span!");
    v.push_back(n);
}

int Span::shortestSpan()
{
    if (v.size() < 2)
        throw std::runtime_error("no enough elements in Span!");
    std::sort(v.begin(), v.end());
    int def = *(v.begin() + 1) - *v.begin();
    for (std::vector<int> :: iterator it = v.begin() + 2; it != v.end(); it++)
    {
        if (*it - *(it - 1) < def)
            def = *it - *(it - 1);
    }
    return def;
}

int Span::longestSpan()
{
    if (v.size() < 2)
        throw std::runtime_error("no enough elements in Span!");
    std::sort(v.begin(), v.end());
    return *(v.end() - 1) -  *v.begin();
}