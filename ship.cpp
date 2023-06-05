#include "ship.h"

using namespace std;

#ifndef SHIP_CPP
#define SHIP_CPP

bool Ship::navigate(Board board, coordinate &startPoint)
{
    coordinate temp;
    coordinate change;
    char typed = 0;
    while (1)
    {
        switch (typed = getch())
        {
        case KEY_UP:
            change.updateXY(-1,0);
            temp = startPoint + change;
            if(shipFit(board, temp)){
                startPoint.updateXY(temp.x,temp.y);
            }
            return false;
        case KEY_DOWN:
            change.updateXY(1,0);
            temp = startPoint + change;
            if (shipFit(board, temp))
            {
                startPoint.updateXY(temp.x,temp.y);
            }
            return false;
        case KEY_RIGHT:
            change.updateXY(0,1);
            temp = startPoint + change;
            if (shipFit(board, temp))
            {
                startPoint.updateXY(temp.x,temp.y);
            }
            return false;
        case KEY_LEFT:
            change.updateXY(0,-1);
            temp = startPoint + change;
            if (shipFit(board, temp))
            {
                startPoint.updateXY(temp.x,temp.y);
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

void Ship::changeOrientation()
{
    for (int i = 0; i < length; i++)
    {
        int temp = shape[i].x;
        shape[i].x = shape[i].y;
        shape[i].y = temp;
    }
}

void Ship::defineShape(){
    for (int i = 0; i < length; i++)
    {
        // horizontal by default
        shape.push_back(coordinate(0, i));
    }
}

bool Ship::shipFit(Board board, coordinate start)
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

int Ship::intersectShip(Board board, coordinate startPoint) // does it cross other ships
{
    coordinate temp;
    for (int i = 0; i < length; i++)
    {
        temp = startPoint + shape[i];
        if (board.checkEmptySpace(temp) == false)
        {
            return NOTVALID;
        }
    }

    return VALID;
}

void Ship::draw(Board &board, coordinate startPoint, int validPlace, bool final)
{
    int color = INVALID_PLACE_C;
    if (validPlace == VALID)
    {
        color = VALID_PLACE_C;
    }
    
    if(final == true){
        color = FIXED_PLACE_C;
    }

    for (int i = 0; i < length; i++)
    {
        coordinate temp = startPoint + shape[i];
        board.draw(temp, symbol, color);
    }
}

void Ship::erase(Board &board, Board original, coordinate startPoint, vector<coordinate> oldShape)
{
    for (int i = 0; i < oldShape.size(); i++)
    {
        coordinate p = startPoint + shape[i];
        char sym = original.get(p);
        int col = original.getColor(p);
        board.draw(p, sym, col);
    }
}

void Ship::display(Board b)
{
    cout << name << " placement \n";
    b.display();
}


void Ship::placeShipInstructions(){
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

Ship::Ship(string n, char sym, int l)
{
    name = n;
    symbol = sym;
    length = l;

    defineShape();
}

int Ship::shipHit()
{
    length--;
    return length;
}

int Ship::getLength()
{
    return length;
}

char Ship::getSymbol()
{
    return symbol;
}


string Ship::getName()
{
    return name;
}

void Ship::placeShip(Board &board)
{
    bool Chosen = false;
    int validPlace = NOTVALID;
    Board temp(board);
    coordinate startPoint(board.lowerLimit, board.lowerLimit);
    coordinate prev(board.lowerLimit, board.upperLimit);
    vector<coordinate> prevShape = shape;
    while (!Chosen || !validPlace)
    {
        validPlace = intersectShip(temp, startPoint); // does it intersect or not
        draw(temp, startPoint, validPlace);
        temp.display();
        placeShipInstructions();
        erase(temp, board, startPoint, prevShape);
        Chosen = navigate(temp, startPoint);
        system("CLS");
        prevShape = shape;
    }

    draw(board, startPoint, VALID, true);
    return;
}

#endif