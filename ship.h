#include <vector>
#include <string>
#include "util.h"
#include <conio.h>
#include <iostream>
#include "board.h"
#include "coordinate.h"

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

    bool navigate(Board board, coordinate &startPoint)
    {
        char typed = 0;
        coordinate temp;
        while (1)
        {
            switch (typed = getch())
            {
            case KEY_UP:
                temp.x = startPoint.x - 1;
                temp.y = startPoint.y;
                if (shipFit(board, temp))
                {
                    startPoint.x = temp.x;
                    startPoint.y = temp.y;
                }
                return false;
            case KEY_DOWN:
                temp.x = startPoint.x + 1;
                temp.y = startPoint.y;
                if (shipFit(board, temp))
                {
                    startPoint.x = temp.x;
                    startPoint.y = temp.y;
                }
                return false;
            case KEY_RIGHT:
                temp.x = startPoint.x;
                temp.y = startPoint.y + 1;
                if (shipFit(board, temp))
                {
                    startPoint.x = temp.x;
                    startPoint.y = temp.y;
                }
                return false;
            case KEY_LEFT:
                temp.x = startPoint.x;
                temp.y = startPoint.y - 1;
                if (shipFit(board, temp))
                {
                    startPoint.x = temp.x;
                    startPoint.y = temp.y;
                }
                return false;
            case FINISHED:
                return true;
            case ORIENTATION:
                changeOrientation();
                if (shipFit(board, startPoint) == false)
                {
                    changeOrientation();
                }
                return false;
            default:
                break;
            }
        }
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

    bool shipFit(Board board, coordinate start)
    {
        coordinate temp;
        for (int i = 0; i < length; i++)
        {
            temp = start + shape[i];
            if (board.checkBoardBoundary(temp) == false)
            {
                return false;
            }
        }
        return true;
    }
    int checkValidity(Board board, coordinate startPoint) // does it cross other ships
    {
        for (int i = 0; i < length; i++)
        {
            coordinate temp = startPoint + shape[i];
            if (board.checkEmptySpace(temp) == false)
            {
                return NOTVALID;
            }
        }

        return VALID;
    }
    void draw(Board board, coordinate startPoint, int validPlace)
    {
        int color = 0;
        if (validPlace == VALID)
        {
            color = 1;
        }
        for (int i = 0; i < length; i++)
        {
            coordinate temp = startPoint + shape[i];
            board.draw(temp, symbol, 0);
        }
    }
    void erase(Board board, coordinate startPoint);

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

    void placeShip(Board board)
    {
        bool Chosen = false;
        int validPlace = 0;
        coordinate startPoint(board.lowerLimit, board.lowerLimit);
        coordinate prev(board.lowerLimit, board.upperLimit);
        vector<coordinate> prevShape = shape;
        while (!Chosen || !validPlace)
        {
            validPlace = checkValidity(board, startPoint); // does it intersect or not
            draw(board, startPoint, validPlace);
            board.display();
            Chosen = navigate(board, startPoint);
            cout << Chosen << endl;
            cout << startPoint << endl;
            cout << validPlace << endl;
            //  erase(board, startPoint);
            prevShape = shape;
        }

        // draw(board, startPoint, );
        return;
    }
};

#endif