#include <iostream>

#ifndef UTIL_H
#define UTIL_H
// Pressing these keys makes the position on the board move
#define KEY_UP 72    // arrow up key
#define KEY_DOWN 80  // arrow down key
#define KEY_LEFT 75  // arrow left key
#define KEY_RIGHT 77 // arrow right key

// Pressing this button means the player has decided where to set or shoot
#define FINISHED 13 // enter button.

// Ship placement descriptions
#define SHIPSET 2
#define VALID 1
#define NOTVALID 0

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