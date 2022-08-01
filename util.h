#include <iostream>

using namespace std;

#ifndef UTIL_H
#define UTIL_H

struct Board
{
    char **board;
    int sizeOfBoard;

public:
    Board()
    {
        sizeOfBoard = 12;
    }
    Board(int s)
    {
        sizeOfBoard = s;
    }

    void display()
    {
        for (int i = 0; i < sizeOfBoard; i++)
        {
            for (int j = 0; j < sizeOfBoard; j++)
            {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
};

struct coordinate
{
    int x;
    int y;

    coordinate(int a, int b)
    {
        x = a;
        y = b;
    }
};

#endif