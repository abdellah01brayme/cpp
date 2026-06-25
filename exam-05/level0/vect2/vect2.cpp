#include "vect2.hpp"

vect2::vect2():x(0), y(0)
{

}
vect2::vect2(const int x, const int y):x(x), y(y)
{

}
vect2::vect2(const vect2 &other):x(other.x), y(other.y)
{

}
vect2::~vect2()
{

}
vect2& vect2::operator=(const vect2 &other)
{
    if (*this != other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}
const int &vect2::operator[](const int index) const
{
    if (index == 0)
        return x;
    return y;
}
int &vect2::operator[](const int index)
{
    if (index == 0)
        return x;
    return y;
}
const vect2 vect2::operator+(const vect2 &other) const
{
    return vect2(this->x + other.x, this->y + other.y);
}
const vect2 vect2::operator-(const vect2 &other) const
{
    return vect2(this->x - other.x, this->y - other.y);
}
vect2 &vect2::operator+=(const vect2 &other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}
vect2 &vect2::operator-=(const vect2 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
const vect2 vect2::operator*(const int n) const
{
    return vect2(x * n, y * n);
}
vect2 &vect2::operator*=(const int n)
{
    x *= n;
    y *= n;
    return *this;
}
vect2 &vect2::operator++()
{
    x++;
    y++;
    return *this;
}
vect2 vect2::operator++(int)
{
    vect2 v(x++, y++);
    return v;
}
vect2 &vect2::operator--()
{
    x--;
    y--;
    return *this;
}
vect2 vect2::operator--(int)
{
    return vect2(x--, y--);
}

vect2 vect2::operator-() const
{
    return vect2(-x, -y);
}
bool vect2::operator==(const vect2& other) const
{
    if (x == other.x && y == other.y)
        return true;
    return false;
}
bool vect2::operator!=(const vect2& other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &out, const vect2 &other)
{
    out << "{" << other[0] << ", " << other[1] << "}" << std::endl;
    return out;
}
vect2 operator*(const int n, const vect2 &other)
{
    return (vect2(n * other[0], n*other[1]));
}