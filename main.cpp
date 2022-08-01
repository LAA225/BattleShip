/*to activate sound, go to settings -> compiler settings -> linker settings ->
in the link libraries section, add winmm and select pk.*/

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <MMSystem.h>
#include <string>
#include "main.h"

using namespace std;

BattleShip::BattleShip()
{
    firstscreen();
    rules();

    // setup all player boards
    system("CLS");
    cout << "Let the war begin!" << endl
         << endl;

    cout << "Due to resource limitation,"
         << "only one player can set their board"
         << "at a time and the other player must turn away " << endl
         << endl
         << "First turn goes to player 1!" << endl;
    setplayer(setBoard1);
    Sleep(4000);
    system("CLS");
    rules();
    system("CLS");

    cout << endl
         << endl
         << "Now it is player 2's turn!" << endl;
    setplayer(setBoard2);

    newboard(player1Board);
    newboard(player2Board);

    Sleep(4000);
    system("CLS");

    // begin game
    shoot_p1(setBoard1, setBoard2, player1Board, player2Board);
}

void BattleShip::gameend(char **board, string player)
{
    int counter = 0;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if ((board[i][j] >= 'A') && (board[i][j] <= 'S'))
                counter++;
        }
    }
    if (counter == 0)
    {
        Sleep(1000);
        system("CLS");
        system("COLOR 3F");
        cout << endl
             << endl
             << endl
             << endl
             << "                        "
             << player << "has won the game!!"
             << endl
             << endl;
        // PlaySound(TEXT("Win1.wav"), NULL, SND_SYNC);
        Sleep(1000);
        system("COLOR 07");
        exit(0);
    }
}

char BattleShip::shipsink(char **board, char letter)
{
    // allows function to jump to S as no letter before
    if (letter == 'E')
    {
        letter = 'R';
    }

    if (letter == 'T')
        return 'T';

    int counter = 0;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (board[i][j] == letter)
                counter++;
        }
    }
    if ((counter == 0) && (letter == 'A'))
    {
        cout << "You have sunk your enemy's aircraft carrier!" << endl;
    }
    if ((counter == 0) && (letter == 'B'))
    {
        cout << "You have sunk your enemy's battleship!" << endl;
    }
    if ((counter == 0) && (letter == 'C'))
    {
        cout << "You have sunk your enemy's cruiser!" << endl;
    }
    if ((counter == 0) && (letter == 'D'))
    {
        cout << "You have sunk your enemy's destroyer!" << endl;
    }
    if ((counter == 0) && (letter == 'S'))
    {
        cout << "You have sunk your enemy's submarine!" << endl;
    }
    shipsink(board, letter + 1);

    return letter;
}
void BattleShip::firstscreen()
{
    system("COLOR 3F");
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "        ___            _____  _____         ____   __            __  " << endl
         << "       |   \\    /\\       |      |    |     |      /  \\ |   |  | |  \\ " << endl
         << "       |___/   /__\\      |      |    |     |____  \\__  |___|  | |__/ " << endl
         << "       |   \\  /    \\     |      |    |     |         \\ |   |  | |    " << endl
         << "       |___/ /      \\    |      |    |____ |____  \\__/ |   |  | |    " << endl;

    cout << endl
         << endl
         << "                              Version 1.0" << endl;
    cout << "                             By Laiba Abid" << endl
         << endl;
    cout << "                               Loading";

    Sleep(500);
    cout << ".";
    Beep(250, 500);
    Sleep(500);
    cout << ".";
    Beep(250, 500);
    Sleep(500);
    cout << ".";
    Beep(250, 500);
    Sleep(500);
    cout << ".";
    Beep(250, 500);
    Sleep(1000);
    system("CLS");
    system("COLOR 07");
}

void BattleShip::shoot_p2(char **board1, char **board2, char **boardp1, char **boardp2)
{
    string consequence;
    int x, y;
    cout << endl;
    cout << "Player 2's turn." << endl;
    display(boardp2);
    cout << "Enter coordinates: " << endl;
    cout << "x: ";
    cin >> x;
    while ((x > 9) || (x < 0))
    {
        cout << "Error! x coordinate should be between 0-9." << endl
             << endl;
        cout << "x: ";
        cin >> x;
    }

    cout << "y: ";
    cin >> y;
    while ((y > 9) || (y < 0))
    {
        cout << "Error! y coordinate should be between 0-9." << endl
             << endl;
        cout << "y: ";
        cin >> y;
    }

    if ((board1[x + 1][y + 1] >= 'A') && (board1[x + 1][y + 1] <= 'S'))
    {
        char letter = 'A';
        string player = "Player 2 ";
        cout << "A ship has been hit!" << endl;
        consequence = "hit";
        // PlaySound(TEXT("Hit2.wav"), NULL, SND_SYNC);
        changeboard(consequence, board1, boardp2, x, y);
        shipsink(board1, letter);
        gameend(board1, player);
        cout << endl;
        cout << "Player 2 gets another turn." << endl;
        shoot_p2(board1, board2, boardp1, boardp2);
    }
    else
    {
        cout << "Nothing was hit" << endl;
        consequence = "miss";
        // PlaySound(TEXT("Miss2.wav"), NULL, SND_SYNC);
        changeboard(consequence, board1, boardp2, x, y);
        shoot_p1(board1, board2, boardp1, boardp2);
    }
}

void BattleShip::shoot_p1(char **board1, char **board2, char **boardp1, char **boardp2)
{
    string consequence;
    int x, y;
    cout << endl;
    cout << "Player 1's turn." << endl;
    display(boardp1);
    cout << "Enter coordinates: " << endl;
    cout << "x: ";
    cin >> x;
    while ((x > 9) || (x < 0))
    {
        cout << "Error! x coordinate should be between 0-9." << endl
             << endl;
        cout << "x: ";
        cin >> x;
    }

    cout << "y: ";
    cin >> y;
    while ((y > 9) || (y < 0))
    {
        cout << "Error! y coordinate should be between 0-9." << endl
             << endl;
        cout << "y: ";
        cin >> y;
    }

    if ((board2[x + 1][y + 1] >= 'A') && (board2[x + 1][y + 1] <= 'S'))
    {
        char letter = 'A';
        string player = "Player 1 ";
        cout << "A ship has been hit!" << endl;
        // PlaySound(TEXT("Hit2.wav"), NULL, SND_SYNC);
        consequence = "hit";
        changeboard(consequence, board2, boardp1, x, y);
        shipsink(board2, letter);
        gameend(board2, player);
        cout << endl;
        cout << "Player 1 gets another turn." << endl;
        shoot_p1(board1, board2, boardp1, boardp2);
    }
    else
    {
        cout << "Nothing was hit" << endl;
        consequence = "miss";
        // PlaySound(TEXT("Miss2.wav"), NULL, SND_SYNC);
        changeboard(consequence, board2, boardp1, x, y);
        shoot_p2(board1, board2, boardp1, boardp2);
    }
}
void BattleShip::changeboard(string cons, char **board_of_opponent, char **board_of_player, int x, int y)
{
    if (cons == "hit")
    {
        board_of_player[x + 1][y + 1] = 'X';
    }
    if (cons == "miss")
    {
        board_of_player[x + 1][y + 1] = '*';
    }
    display(board_of_player);
    Sleep(1000);
    system("CLS");
    board_of_opponent[x + 1][y + 1] = '.';
}

void BattleShip::setplayer(char **board)
{
    cout << "First turn goes to player 1!" << endl;
    newboard(board);
    display(board);
    carrier(board);
    battleship(board);
    cruiser(board);
    submarine(board);
    destroyer(board);
}

void BattleShip::carrierinput(int &i, int &j, string &pos, char **board)
{
    cout << endl;
    cout << "Input starting coordinates" << endl;

    cout << "x: ";
    cin >> i;
    while ((i > 9) || (i < 0))
    {
        cout << "Error! x coordinate should be between 0-9." << endl
             << endl;
        cout << "x: ";
        cin >> i;
    }

    cout << "y: ";
    cin >> j;
    while ((j > 9) || (j < 0))
    {
        cout << "Error! y coordinate should be between 0-9." << endl
             << endl;
        cout << "y: ";
        cin >> j;
    }

    cout << "Input orientation: ";
    cin >> pos;
    while ((pos != "v") && (pos != "h"))
    {
        cout << "Error! Position can only be 'v' or 'h'." << endl
             << endl;
        cout << "Input orientation: ";
        cin >> pos;
    }

    checkcarrier(i, j, pos, board);
}

void BattleShip::checkcarrier(int &i, int &j, string &pos, char **board)
{
    bool error = 0;

    if (pos == "h")
    {
        if ((i < 1) || (i > 8) || (j > 7))
        {
            error = 1;
        }
    }
    if (pos == "v")
    {
        if ((j < 1) || (j > 8) || (i > 7))
        {
            error = 1;
        }
    }

    if (error == 1)
    {
        cout << "Ship cannot be placed. Please re-enter coordinates." << endl;
        carrierinput(i, j, pos, board);
    }
}
void BattleShip::carrier(char **board)
{
    int i, j;
    string pos;
    cout << "Placement of carrier";
    carrierinput(i, j, pos, board);

    if (pos == "h")
    {
        for (int n = 0; n < 3; n++)
            board[i + 1][j + 1 + n] = 'A';
        for (int n = 0; n < 3; n++)
            board[i + n][j + 1] = 'A';
    }

    if (pos == "v")
    {
        for (int n = 0; n < 3; n++)
            board[i + 1][j + n] = 'A';
        for (int n = 0; n < 3; n++)
            board[i + 1 + n][j + 1] = 'A';
    }
    display(board);
}
void BattleShip::battleship(char **board)
{
    int size_of_ship = 4;
    int i, j;
    string pos = "";

    cout << "Placement of battleship";
    input(i, j, pos, size_of_ship, board);

    if (pos == "h")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + 1][j + n + 1] = 'B';
    }

    if (pos == "v")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + n + 1][j + 1] = 'B';
    }
    display(board);
}
void BattleShip::cruiser(char **board)
{
    int size_of_ship = 3;
    int i, j;
    string pos = "";

    cout << "Placement of cruiser";
    input(i, j, pos, size_of_ship, board);

    if (pos == "h")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + 1][j + n + 1] = 'C';
    }

    if (pos == "v")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + n + 1][j + 1] = 'C';
    }
    display(board);
}
void BattleShip::submarine(char **board)
{
    int size_of_ship = 3;
    int i, j;
    string pos = "";

    cout << "Placement of submarine";
    input(i, j, pos, size_of_ship, board);

    if (pos == "h")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + 1][j + n + 1] = 'S';
    }

    if (pos == "v")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + n + 1][j + 1] = 'S';
    }
    display(board);
}
void BattleShip::destroyer(char **board)
{
    int size_of_ship = 2;
    int i, j;
    string pos = "";

    cout << "Placement of destroyer";
    input(i, j, pos, size_of_ship, board);

    if (pos == "h")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + 1][j + n + 1] = 'D';
    }

    if (pos == "v")
    {
        for (int n = 0; n < size_of_ship; n++)
            board[i + n + 1][j + 1] = 'D';
    }
    display(board);
}

void BattleShip::display(char **board)
{
    cout << endl;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

void BattleShip::newboard(char **board)
{
    for (int i = 0; i < sizeOfBoard; i++)
    {
        for (int j = 0; j < sizeOfBoard; j++)
        {
            board[i][j] = '.';
        }
    }

    for (int i = 1; i < sizeOfBoard; i++)
    {
        board[i][0] = '0' + i - 1;
        for (int j = 0; j < sizeOfBoard; j++)
        {
            board[0][j] = '0' + j - 1;
            board[0][0] = '-';
        }
    }
}
void BattleShip::input(int &i, int &j, string &pos, int &size_of_ship, char **board)
{
    cout << endl;
    cout << "Input starting coordinates" << endl;

    cout << "x: ";
    cin >> i;
    while ((i > 9) || (i < 0))
    {
        cout << "Error! x coordinate should be between 0-9." << endl
             << endl;
        cout << "x: ";
        cin >> i;
    }

    cout << "y: ";
    cin >> j;
    while ((j > 9) || (j < 0))
    {
        cout << "Error! y coordinate should be between 0-9." << endl
             << endl;
        cout << "y: ";
        cin >> j;
    }

    cout << "Input orientation: ";
    cin >> pos;
    while ((pos != "v") && (pos != "h"))
    {
        cout << "Error! Position can only be 'v' or 'h'." << endl
             << endl;
        cout << "Input orientation: ";
        cin >> pos;
    }

    check(i, j, pos, size_of_ship, board);
}

void BattleShip::check(int &i, int &j, string &pos, int &size_of_ship, char **board)
{
    bool error = 0;

    if (pos == "h")
    {
        for (int n = 0; n < size_of_ship; n++)
        {
            if (board[i + 1][j + 1 + n] != '.')
            {
                error = 1;
            }
        }

        if (((j + size_of_ship + 1) == 11) && (i == 9))
        {
            for (int n = 0; n < size_of_ship + 1; n++)
            {
                if ((board[i][j + n] == 'A') || (board[i][j + n] == 'B') || (board[i][j + n] == 'C') || (board[i][j + n] == 'D') || (board[i][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 1][j + n] == 'A') || (board[i + 1][j + n] == 'B') || (board[i + 1][j + n] == 'C') || (board[i + 1][j + n] == 'D') || (board[i + 1][j + n] == 'S'))
                {
                    error = 1;
                }
            }
        }
        else if ((j + size_of_ship + 1) == 11)
        {
            for (int n = 0; n < size_of_ship + 1; n++)
            {
                if ((board[i][j + n] == 'A') || (board[i][j + n] == 'B') || (board[i][j + n] == 'C') || (board[i][j + n] == 'D') || (board[i][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 1][j + n] == 'A') || (board[i + 1][j + n] == 'B') || (board[i + 1][j + n] == 'C') || (board[i + 1][j + n] == 'D') || (board[i + 1][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 2][j + n] == 'A') || (board[i + 2][j + n] == 'B') || (board[i + 2][j + n] == 'C') || (board[i + 2][j + n] == 'D') || (board[i + 2][j + n] == 'S'))
                {
                    error = 1;
                }
            }
        }
        else if (i == 9)
        {
            for (int n = 0; n < size_of_ship + 2; n++)
            {
                if ((board[i][j + n] == 'A') || (board[i][j + n] == 'B') || (board[i][j + n] == 'C') || (board[i][j + n] == 'D') || (board[i][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 1][j + n] == 'A') || (board[i + 1][j + n] == 'B') || (board[i + 1][j + n] == 'C') || (board[i + 1][j + n] == 'D') || (board[i + 1][j + n] == 'S'))
                {
                    error = 1;
                }
            }
        }

        else
        {
            for (int n = 0; n < size_of_ship + 2; n++)

            {
                if ((board[i][j + n] == 'A') || (board[i][j + n] == 'B') || (board[i][j + n] == 'C') || (board[i][j + n] == 'D') || (board[i][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 1][j + n] == 'A') || (board[i + 1][j + n] == 'B') || (board[i + 1][j + n] == 'C') || (board[i + 1][j + n] == 'D') || (board[i + 1][j + n] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + 2][j + n] == 'A') || (board[i + 2][j + n] == 'B') || (board[i + 2][j + n] == 'C') || (board[i + 2][j + n] == 'D') || (board[i + 2][j + n] == 'S'))
                {
                    error = 1;
                }
            }
        }
    }

    if (pos == "v")
    {
        for (int n = 0; n < size_of_ship; n++)
        {
            if (board[i + 1 + n][j + 1] != '.')
            {
                error = 1;
            }
        }

        if (((i + size_of_ship + 1) == 11) && (j == 9))
        {
            for (int n = 0; n < size_of_ship + 1; n++)
            {
                if ((board[i + n][j] == 'A') || (board[i + n][j] == 'B') || (board[i + n][j] == 'C') || (board[i + n][j] == 'D') || (board[i + n][j] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 1] == 'A') || (board[i + n][j + 1] == 'B') || (board[i + n][j + 1] == 'C') || (board[i + n][j + 1] == 'D') || (board[i + n][j + 1] == 'S'))
                {
                    error = 1;
                }
            }
        }

        else if ((i + size_of_ship + 1) == 11)
        {
            for (int n = 0; n < size_of_ship + 1; n++)
            {
                if ((board[i + n][j] == 'A') || (board[i + n][j] == 'B') || (board[i + n][j] == 'C') || (board[i + n][j] == 'D') || (board[i + n][j] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 1] == 'A') || (board[i + n][j + 1] == 'B') || (board[i + n][j + 1] == 'C') || (board[i + n][j + 1] == 'D') || (board[i + n][j + 1] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 2] == 'A') || (board[i + n][j + 2] == 'B') || (board[i + n][j + 2] == 'C') || (board[i + n][j + 2] == 'D') || (board[i + n][j + 2] == 'S'))
                {
                    error = 1;
                }
            }
        }
        else if (j == 9)
        {
            for (int n = 0; n < size_of_ship + 2; n++)
            {
                if ((board[i + n][j] == 'A') || (board[i + n][j] == 'B') || (board[i + n][j] == 'C') || (board[i + n][j] == 'D') || (board[i + n][j] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 1] == 'A') || (board[i + n][j + 1] == 'B') || (board[i + n][j + 1] == 'C') || (board[i + n][j + 1] == 'D') || (board[i + n][j + 1] == 'S'))
                {
                    error = 1;
                }
            }
        }

        else
        {
            for (int n = 0; n < size_of_ship + 2; n++)
            {
                if ((board[i + n][j] == 'A') || (board[i + n][j] == 'B') || (board[i + n][j] == 'C') || (board[i + n][j] == 'D') || (board[i + n][j] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 1] == 'A') || (board[i + n][j + 1] == 'B') || (board[i + n][j + 1] == 'C') || (board[i + n][j + 1] == 'D') || (board[i + n][j + 1] == 'S'))
                {
                    error = 1;
                }
                if ((board[i + n][j + 2] == 'A') || (board[i + n][j + 2] == 'B') || (board[i + n][j + 2] == 'C') || (board[i + n][j + 2] == 'D') || (board[i + n][j + 2] == 'S'))
                {
                    error = 1;
                }
            }
        }
    }

    if (error == 1)
    {
        cout << "Ship cannot be placed. Please re-enter coordinates." << endl;
        input(i, j, pos, size_of_ship, board);
    }
}

void BattleShip::rules()
{

    cout << "                        -X-X-X-   RULES   -X-X-X-" << endl
         << endl;
    cout << "OBJECTIVES:" << endl;
    cout << "The object of Battleship is to try and sink all of the other player's ships" << endl
         << "before they sink all of your ships." << endl
         << "Neither of the players can see the other's board so they must guess where" << endl
         << "they are." << endl
         << endl;
    cout << "PLACEMENT:" << endl;
    cout << "Each player is to set their grids one by one." << endl
         << "Each player places the 5 ships somewhere on their board." << endl
         << "The ships can only be placed vertically or horizontally." << endl
         << "Diagonal placement is not allowed." << endl
         << "No part of a ship may hang off the edge of the board." << endl
         << "Ships may not overlap each other." << endl
         << "No two ships can share an adjacent square horizontally," << endl
         << "vertically or diagonally." << endl
         << "Ships can be placed by inputting the starting coordinates" << endl
         << "of a ship along with its orientation ('v' for vertical and 'h' for horizontal)." << endl
         << "Once the ship has been placed, the players may not move the ships." << endl
         << "The 5 ships are:  Carrier (occupies 5 spaces in the shape of a T)," << endl
         << "Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2)." << endl
         << endl;
    cout << "SHOOTING:" << endl
         << "Each player will try and hit the opponent's ship by calling out" << endl
         << "the coordinates of one of the squares on the board." << endl
         << "If a player hits his opponent's ship," << endl
         << "a hit is declared by an 'X' on the grid. " << endl
         << "A miss is marked with a '*'" << endl
         << "If it is a hit, the player gets another turn otherwise the turn is" << endl
         << "passed on to the other player." << endl
         << "The game ends when all the ships of one player have been sunk." << endl
         << endl
         << endl;

    char check;
    cout << "Press 'P' to play and 'Q' to quit: ";
    cin >> check;
    if (!((check == 'P') || (check == 'p')))
        exit(0);
}

int main()
{
    BattleShip NewGame;
    return 0;
}
