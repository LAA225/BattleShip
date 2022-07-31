#include <string>

using namespace std;

#ifndef MAIN_H
#define MAIN_H

class BattleShip
{
    // size of board
    const int sizeOfBoard = 11;
    // player 1 board with set ships
    char **setBoard1 = NULL;
    // player 1 board for playing
    char **player1Board = NULL;

    // player 2 board with set ships
    char **setBoard2 = NULL;
    // player 1 board for playing
    char **player2Board = NULL;

    void rules();
    void setplayer(char **board);

    void display(char **board);
    void newboard(char **board);
    void carrier(char **board);
    void battleship(char **board);
    void cruiser(char **board);
    void submarine(char **board);
    void destroyer(char **board);
    void check(int &i, int &j, string &pos, int &size_of_ship, char **board);
    void input(int &i, int &j, string &pos, int &size_of_ship, char **board);
    void carrierinput(int &i, int &j, string &pos, char **board);
    void checkcarrier(int &i, int &j, string &pos, char **board);
    void shoot_p2(char **board1, char **board2, char **boardp1, char **boardp2);
    void shoot_p1(char **board1, char **board2, char **boardp1, char **boardp2);
    void changeboard(string cons, char **board_of_opponent, char **board_of_player, int x, int y);
    void firstscreen();
    char shipsink(char **board, char letter);
    void gameend(char **board, string player);

public:
    BattleShip();
};

#endif