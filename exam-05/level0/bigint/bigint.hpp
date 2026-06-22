#pragma once
#include <iostream>
#include <string>
#include <sstream>

class bigint
{
    private:
        std::string buf;
        int getint() const;
    public:
        bigint();
        bigint(int n);
        bigint(const bigint &other);
        ~bigint();
        bigint& operator=(const bigint &other);
        bigint operator+(const bigint &other) const;
        bigint operator>>(const int n);
        bigint operator<<(const int n);
        bigint& operator<<=(const int n);
        bigint& operator>>=(const int n);
        bigint operator>>(const bigint &other);
        bigint operator<<(const bigint &other);
        bigint& operator<<=(const bigint &other);
        bigint& operator>>=(const bigint &other);
        bigint& operator+=(const bigint& n);
        bigint& operator++();
        bigint operator++(int);
        
        bool operator==(const bigint &other) const;
        bool operator!=(const bigint &other) const;
        bool operator>(const bigint &other) const;
        bool operator>=(const bigint &other) const;
        bool operator<(const bigint &other) const;
        bool operator<=(const bigint &other) const;
        std::string getstr() const;
};
std::ostream &operator<<(std::ostream &in, const bigint &other);