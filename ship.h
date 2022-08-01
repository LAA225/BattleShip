#include <vector>
#include <string>
#include "coordinate.h"
#include <iostream>
using namespace std;

#ifndef SHIP_H
#define SHIP_H

class Ship
{
protected:
    string name;
    char symbol;
    int length;
    vector<coordinate> shape;

    coordinate navigate(char **board)
    {
        // move the cursor around and pick what fits
    }

public:
    Ship() {}

    Ship(string n, char sym, int l)
    {
        name = n;
        symbol = sym;
        length = l;

        for (int i = 0; i < length; i++)
        {
            // horizontal by default
            shape.push_back(coordinate(0, i));
        }
    }
    int shipHit()
    {
        length--;
        return length;
    }

    int getLength()
    {
        return length;
    }

    // change shape from horizontial to vertical or vice versa
    void changeOrientation()
    {
        for (int i = 0; i < length; i++)
        {
            int temp = shape[i].x;
            shape[i].x = shape[i].y;
            shape[i].y = temp;
        }
    }

    void placeShip(char **board)
    {
        coordinate start = navigate(board);

        for (int i = 0; shape.size(); i++)
        {
            board[start.x + shape[i].x][start.y + shape[i].y] = symbol;
        }
    }
};

#endif