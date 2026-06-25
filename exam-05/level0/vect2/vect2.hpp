#include <iostream>


class vect2
{
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(const int x, const int y);
        vect2(const vect2 &other);
        ~vect2();
        vect2& operator=(const vect2 &other);
        const int &operator[](const int index) const;
        int &operator[](const int index);
        const vect2 operator+(const vect2 &other) const;
        const vect2 operator-(const vect2 &other) const;
        vect2 &operator+=(const vect2 &other);
        vect2 &operator-=(const vect2 &other);
        const vect2 operator*(const int n) const;
        vect2 &operator*=(const int n);
        vect2 &operator++();
        vect2 operator++(int);
        vect2 &operator--();
        vect2 operator--(int);
        vect2 operator-() const;
        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;

};
std::ostream &operator<<(std::ostream &out, const vect2 &other);
vect2 operator*(const int n, const vect2 &other);
