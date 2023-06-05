// Board.h
#include <iostream>
#include "util.h"
#include "coordinate.h"

#ifndef BOARD_H
#define BOARD_H

class Board
{
    // the symbols at every position on the board are represented
    char **board;
    int sizeOfBoard;
    
    // the colors at every position on the board are represented
    int **color;

public:
    // defines the left and down boundary of the board
    int lowerLimit;

    // defines the right and up boundary of the board
    int upperLimit;

    Board();
    Board(int s);
    Board(const Board &b);

    // display the board on the terminal
    void display();

    // creates new empty board 
    void initializeBoard();

    // checks if a coordinate is within board boundaries
    bool checkBoardBoundary(coordinate point);

    // checks if a coordinate points to an empty space
    bool checkEmptySpace(coordinate point);
    
    // marks the coordinate on the baord with the given symbol and color
    void draw(coordinate point, char symbol, int colorOfSymbol);
    
    // returns the symbol at the coordinate on the board
    char get(coordinate point);
    
    // returns the color at the coordinate on the board
    int getColor(coordinate point);
    
};

#endif