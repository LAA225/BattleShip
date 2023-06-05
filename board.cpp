#include "board.h"

using namespace std;

#ifndef BOARD_CPP
#define BOARD_CPP

Board::Board()
{
    sizeOfBoard = 12;
    lowerLimit = 1;
    upperLimit = 10;
    initializeBoard();
}
Board::Board(int s)
{
    if (s < 10)
    {
        cout << "board is being set to minimum size of 10" << endl;
        s = 10;
    }

    sizeOfBoard = s;
    lowerLimit = 1;
    upperLimit = s - 2;
    initializeBoard();
}
Board::Board(const Board &b)
{
    sizeOfBoard = b.sizeOfBoard;
    lowerLimit = b.lowerLimit;
    upperLimit = b.upperLimit;
    initializeBoard();
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            board[i][j] = b.board[i][j];
            color[i][j] = b.color[i][j];
        }
    }
}

void Board::display()
{
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            Color(color[i][j]);
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

void Board::initializeBoard()
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
    // color board initialize
    color = new int *[sizeOfBoard];
    for (int i = 0; i < sizeOfBoard; i++)
    {
        color[i] = new int[sizeOfBoard];
    }
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            color[i][j] = EMPTY_C;
        }
    }
}
bool Board::checkBoardBoundary(coordinate point)
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

bool Board::checkEmptySpace(coordinate point)
{
    if (board[point.x][point.y] == '.')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Board::draw(coordinate point, char symbol, int colorOfSymbol)
{
    board[point.x][point.y] = symbol;
    color[point.x][point.y] = colorOfSymbol;
    return;
}
char Board::get(coordinate point)
{
    if (point.x < sizeOfBoard && point.x > -1 && point.y < sizeOfBoard && point.y > -1)
    {
        return board[point.x][point.y];
    }
    return ' ';
}
int Board::getColor(coordinate point)
{
    if (point.x < sizeOfBoard && point.x > -1 && point.y < sizeOfBoard && point.y > -1)
    {
        return color[point.x][point.y];
    }
    return 0;
}

#endif