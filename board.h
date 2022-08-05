#include <iostream>
#include "util.h"

using namespace std;

#ifndef BOARD_H
#define BOARD_H

struct Board
{
    char **board;
    int sizeOfBoard;
    int lowerLimit;
    int upperLimit;

public:
    Board()
    {
        sizeOfBoard = 12;
        lowerLimit = 1;
        upperLimit = 11;
    }
    Board(int s)
    {
        if (s < 10)
        {
            cout << "board is being set to minimum size of 10" << endl;
            s = 10;
        }

        sizeOfBoard = s;
        lowerLimit = 1;
        upperLimit = s - 1;
    }

    void display()
    {
        for (int i = 0; i < sizeOfBoard; i++)
        {
            for (int j = 0; j < sizeOfBoard; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    void initializeBoard()
    {
        board = new char *[sizeOfBoard];
        for (int i = 0; i < sizeOfBoard; i++)
        {
            board[i] = new char[sizeOfBoard];
        }

        for (int i = 0; i < sizeOfBoard; i++)
        {
            for (int j = 0; j < sizeOfBoard; j++)
            {
                if (i == 0)
                {
                    board[i][j] = '_';
                }
                else if (i == sizeOfBoard - 1)
                {
                    board[i][j] = char(196);
                }
                else if (j == 0 || j == sizeOfBoard - 1)
                {
                    board[i][j] = '|';
                }
                else
                {
                    board[i][j] = '.';
                }
            }
        }
    }
    bool checkBoardBoundary(coordinate point)
    {
        if (point.x < lowerLimit || point.x > upperLimit)
        {
            return false;
        }
        if (point.y < lowerLimit || point.y > upperLimit)
        {
            return false;
        }

        return true;
    }
};

#endif