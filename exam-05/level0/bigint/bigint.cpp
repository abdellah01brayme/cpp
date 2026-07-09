#include "bigint.hpp"

bigint::bigint():buf("0"){}

bigint::bigint(int n)
{
    long l = n;
    if (l < 0) l = -l;
    std:: stringstream ss;
    ss << l;

    buf = ss.str();
    std::cout <<"buf : " << buf << std::endl;
}
bigint:: bigint(const bigint &other): buf(other.buf){}

bigint& bigint::operator=(const bigint& other)
{
    buf = other.buf;
    return *this;
}
bigint::~bigint(){}

int bigint::getint() const
{
    std::stringstream ss(this->buf);
    int n;
    ss >> n;
    return n;
}

bigint bigint::operator+(const bigint &other) const
{
    int i = this->buf.length() - 1;
    int j = other.buf.length() - 1;
    bigint result;
    result.buf.clear();
    int left = 0, tmp = 0;
    for (; i >=0 && j >= 0; i--, j--)
    {
        tmp = this->buf[i] + other.buf[j] + left - (2 * '0');
        if (tmp > 9)
        {
            tmp -= 10;
            left = 1;
        }
        else
            left = 0;
        result.buf.insert(result.buf.begin(), tmp + '0');
    }
    for (; j >= 0; j--)
    {
        tmp = other.buf[j] + left - '0';
        if (tmp > 9)
        {
            tmp -= 10;
            left = 1;
        }
        else
            left = 0;
        result.buf.insert(result.buf.begin(), tmp + '0');
    }
    for (; i >= 0; i--)
    {
        tmp = this->buf[i] + left - '0';
        if (tmp > 9)
        {
            tmp -= 10;
            left = 1;
        }
        else
            left = 0;
        result.buf.insert(result.buf.begin(), tmp + '0');
    }
    return result;
}

bigint bigint::operator>>(const int n)
{
    if (this->buf.length() == 1 && this->buf[0] == '0')
        return *this;
    if (this->buf.length() <= n)
    {
        this->buf = "0";
        return *this;
    }
    this->buf.erase(this->buf.length() - n, n);
    return *this;
}

bigint bigint::operator<<(const int n)
{
    if (this->buf[0] == '0')
        return *this;
    for (int i = 0; i < n; i++)
    {
        buf.append(1, '0');
    }
    return *this;
}

bigint& bigint::operator<<=(const int n)
{
    *this = *this << n;
    return *this;
}
bigint& bigint::operator>>=(const int n)
{
    *this = *this >> n;
    return *this;
}
bigint bigint::operator>>(const bigint &other)
{
    return *this >> other.getint();
}
bigint bigint::operator<<(const bigint &other)
{
    return *this << other.getint();
}
bigint&bigint:: operator<<=(const bigint &other)
{
    *this <<= other.getint();
    return *this;
}
bigint&bigint:: operator>>=(const bigint &other)
{
    *this >>= other.getint();
    return *this;
}
bigint& bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return *this;
}
bigint& bigint::operator++()
{
    *this = *this + bigint(1);
    return *this;
}
bigint bigint::operator++(int)
{
    bigint value(*this);
    *this = *this + bigint(1);
    return value;
}

bool bigint::operator==(const bigint &other) const
{
    if (this->buf.length() != other.buf.length())
        return false;
    for (int i = 0; i < this->buf.length(); i++)
    {
        if (this->buf[i] != other.buf[i])
            return false;
    }
    return true;
}
bool bigint::operator!=(const bigint &other) const
{
    return !(*this == other);
}
bool bigint::operator>(const bigint &other) const
{
    if (this->buf.length() > other.buf.length())
        return true;
    else if (this->buf.length() < other.buf.length())
        return false;
    
    return this->buf > other.buf;
}
bool bigint::operator>=(const bigint &other) const
{
    return (*this > other || *this == other);
}
bool bigint::operator<(const bigint &other) const
{
    return !(*this > other);
}
bool bigint::operator<=(const bigint &other) const
{
    return (*this < other || *this == other);
}
std::string bigint::getstr() const
{
    return buf;
}

std::ostream &operator<<(std::ostream &in, const bigint &other)
{
    in << other.getstr();
    return in;
}
