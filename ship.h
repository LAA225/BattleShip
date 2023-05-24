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

    // control the cursor on the board
    bool navigate(Board board, coordinate &startPoint);
    
    // change shape from horizontial to vertical or vice versa
    void changeOrientation();

    // check if the ship fits in the coordinate given
    bool shipFit(Board board, coordinate start);

    //check if the ship overlaps other ships in the coordinate given
    int checkValidity(Board board, coordinate startPoint); // does it cross other ships

    // draw the ship on the coordinates given using validPlace and final to decide the color. 
    // Final is to set the color to set the ship in its permanent position
    void draw(Board &board, coordinate startPoint, int validPlace, bool final=false);

    // erase the ship off a given coordinate on the board using the version of the board 
    // before the ship was set and the shape of the ship used to set. 
    void erase(Board &board, Board original, coordinate startPoint, vector<coordinate> oldShape);

    // Display the board
    void display(Board b);

    // Instructions to show user on how to place ship
    void placeShipInstructions();

public:
    Ship(){}

    // set the name, symbol and length of a ship
    Ship(string n, char sym, int l);

    // when a ship is hit, its length decreases
    int shipHit();

    // return remaining length
    int getLength();

    // return assigned symbol
    char getSymbol();

    // return assigned name
    string getName();

    // choose where to place a ship on the board given
    void placeShip(Board &board);
    
};

#endif