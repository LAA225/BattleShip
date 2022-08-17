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

    void draw(Board &board, coordinate startPoint, int validPlace)
    {
        int color = INVALID_PLACE_C;
        if (validPlace == VALID)
        {
            color = VALID_PLACE_C;
        }
        for (int i = 0; i < length; i++)
        {
            coordinate temp = startPoint + shape[i];
            board.draw(temp, symbol, color);
        }
    }

    void erase(Board &board, Board original, coordinate startPoint, vector<coordinate> oldShape)
    {
        for (int i = 0; i < oldShape.size(); i++)
        {
            coordinate p = startPoint + shape[i];
            char sym = original.get(p);
            int col = original.getColor(p);
            board.draw(p, sym, col);
        }
    }

    void display(Board b)
    {
        cout << name << " placement \n";
        b.display();
        instructions();
    }

    void instructions()
    {
        cout << "INSTRUCTIONS: \n"
             << "- Use ARROW KEYS to move your cursor to where you wish to place \n"
             << "- Press SPACE BAR to switch orientation of ship \n"
             << "- Press ENTER to shoot \n"
             << "- You can only place a ship where it occupies enough space and doesnot intersect any other\n\n"
             << "KEY: \n";
        Color(VALID_PLACE_C);
        cout << symbol << ": valid area to place ship \n";
        Color(INVALID_PLACE_C);
        cout << symbol << ": Invalid area to place ship \n";
        Color(FIXED_PLACE_C);
        cout << symbol << ": ship is set \n";
    }

public:
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

    char getSymbol()
    {
        return symbol;
    }

    string getName()
    {
        return name;
    }

    void placeShip(Board &board)
    {
        bool Chosen = false;
        int validPlace = NOTVALID;
        Board temp(board);
        coordinate startPoint(board.lowerLimit, board.lowerLimit);
        coordinate prev(board.lowerLimit, board.upperLimit);
        vector<coordinate> prevShape = shape;
        while (!Chosen || !validPlace)
        {
            validPlace = checkValidity(temp, startPoint); // does it intersect or not
            draw(temp, startPoint, validPlace);
            temp.display();
            erase(temp, board, startPoint, prevShape);
            Chosen = navigate(temp, startPoint);
            system("CLS");
            prevShape = shape;
        }

        draw(board, startPoint, FIXED_PLACE_C);
        return;
    }
};

#endif