#include "board.h"
#include "ship.h"
#include "AircraftCarrier.cpp"
#include <unordered_map>

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    string name;
    // records ship placement
    Board shipBoard;
    // records moves made by player
    Board movesBoard;

    // an map of symbols to different types of ships and possible ship class derivatives
    unordered_map<char, Ship *> ships;

    // total ship parts remaining to be hit
    int shipParts = 0;

    // control the cursor on the board
    bool navigate(coordinate &point);

    // allows the player to navigate to a position on the map they want to shoot at during the game
    coordinate chooseLocation(string msg = "");

    // determine if the position chosen the player resulted in a hit or miss
    bool evaluateHit(coordinate p);

    // if a ship part is hit, determines outcome (ship defeated, number of ship parts remaining)
    void handleHit(coordinate p, char hitShip);
    

public:
    Player(string s = "player");
    
    // change the name of the player
    void setName(string s);
    
    // returns name of player
    string getName();

    // defines the different type of ships to be placed on the board
    void setupShips();

    // called when its the player's turn to shoot. handles location and aftermath of shot
    bool shoot(Player *oponent, string msg = "");
    
    // returns the number of ship parts remaining of this player on the board
    int shipPartsRemaining();
    
    // displays the board during the player's turn
    void display(string msg = "");

    // instructions to be displayed to the player during his turn
    void shootInstructions();
};

#endif