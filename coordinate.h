#include <iostream>

#ifndef COORDINATE_H
#define COORDINATE_H

class coordinate
{
public:
    int x;
    int y;

    coordinate()
    {
        x = 0;
        y = 0;
    }
    coordinate(int a, int b)
    {
        x = a;
        y = b;
    }

    friend std::ostream &operator<<(std::ostream &, const coordinate &);
    coordinate operator+(const coordinate &a)
    {
        coordinate ans;
        ans.x = x + a.x;
        ans.y = y + a.y;
        return ans;
    }
};

std::ostream &operator<<(std::ostream &os, const coordinate &a)
{
    os << "x: " << a.x << " y: " << a.y;
    return os;
}

#endif