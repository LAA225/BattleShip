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

    bool navigate(coordinate &point)
    {
        char typed = 0;
        coordinate temp = point;
        while (1)
        {
            switch (typed = getch())
            {
            case KEY_UP:
                temp.x = point.x - 1;
                temp.y = point.y;
                if (movesBoard.checkBoardBoundary(temp))
                {
                    point.x = temp.x;
                    point.y = temp.y;
                }
                return false;

            case KEY_DOWN:
                temp.x = point.x + 1;
                temp.y = point.y;
                if (movesBoard.checkBoardBoundary(temp))
                {
                    point.x = temp.x;
                    point.y = temp.y;
                }
                return false;

            case KEY_RIGHT:
                temp.x = point.x;
                temp.y = point.y + 1;
                if (movesBoard.checkBoardBoundary(temp))
                {
                    point.x = temp.x;
                    point.y = temp.y;
                }
                return false;

            case KEY_LEFT:
                temp.x = point.x;
                temp.y = point.y - 1;
                if (movesBoard.checkBoardBoundary(temp))
                {
                    point.x = temp.x;
                    point.y = temp.y;
                }
                return false;

            case FINISHED:
                return true;
            default:
                break;
            }
        }
    }

    coordinate chooseLocation(string msg = "")
    {
        bool Chosen = false;
        coordinate point(movesBoard.lowerLimit, movesBoard.lowerLimit);
        coordinate prevPoint = point;

        char prevSym = movesBoard.get(point);
        int prevCol = movesBoard.getColor(point);

        while (!Chosen)
        {

            movesBoard.draw(point, SEARCH, SEARCH_C);
            display();
            movesBoard.draw(prevPoint, prevSym, prevCol);
            Chosen = navigate(point);
            prevPoint = point;
            prevSym = movesBoard.get(point);
            prevCol = movesBoard.getColor(point);
            system("CLS");
        }
        return point;
    }

    bool evaluateHit(coordinate p)
    {
        char sym = shipBoard.get(p);
        if (ships.find(sym) == ships.end())
        {
            // music for miss
            return false;
        }
        else
        {
            handleHit(p, sym);
            return true;
        }
    }

    void handleHit(coordinate p, char hitShip)
    {
        // music to announce hit
        int left = ships[hitShip]->shipHit();
        if (left == 0)
        {
            cout << "You sunk your enemy's " << ships[hitShip]->getName() << endl;
            // ships.erase(hitShip);
        }
        shipBoard.draw(p, EMPTY, EMPTY_C);
        shipParts--;
    }

public:
    Player(string s = "player")
    {
        name = s;
    }
    void setName(string s)
    {
        name = s;
    }
    string getName()
    {
        return name;
    }
    void setupShips()
    {
        // to add more ordinary ships, add to these lists. 
        // string name of ship in "names"
        // char symbol of ship in "symbols"
        // int length of ship in "lengths`"
        vector<string> names = {"BattleShip", "Carrier", "Cruiser", "Destroyer"};
        vector<char> symbols = {'B', 'C', 'S', 'D'};
        vector<int> lengths = {5, 4, 3, 2};

        Ship* temp = NULL;
        
        // special ship
        temp = new AircraftCarrier();
        char s = temp->getSymbol();
        shipParts += temp->getLength();
        ships[s] = temp;
        ships[s]->placeShip(shipBoard);

        for (int i = 0; i < names.size(); i++)
        {
            temp = new Ship(names[i], symbols[i], lengths[i]);
            shipParts += lengths[i];
            ships[symbols[i]] = temp;
            ships[symbols[i]]->placeShip(shipBoard);
        }

    }

    bool shoot(Player *oponent, string msg = "")
    {
        coordinate point = chooseLocation(msg);

        bool conclusion = oponent->evaluateHit(point);
        if (conclusion == true)
        {
            movesBoard.draw(point, HIT, HIT_C);
            msg = "HIT!";
        }
        else
        {
            movesBoard.draw(point, MISS, MISS_C);
            msg = "MISS.";
        }
        display(msg);
        waitForUser();

        return conclusion;
    }
    int shipPartsRemaining()
    {
        return shipParts;
    }
    void display(string msg = "")
    {
        cout << msg << endl;
        cout << name << "'s Board" << endl;
        movesBoard.display();
        shootInstructions();
    }

    void shootInstructions()
    {
        cout << "INSTRUCTIONS: \n"
             << "- Use ARROW KEYS to move your cursor to where you wish to shoot \n"
             << "- Press ENTER to shoot \n"
             << "- If you manage to hit your enemy ship, you will get another turn\n\n"
             << "KEY: \n";
        Color(SEARCH_C);
        cout << SEARCH << ": Your Cursor\n";
        Color(HIT_C);
        cout << HIT << ": Hit Ship\n";
        Color(MISS_C);
        cout << MISS << ": Miss shot\n";
        Color(EMPTY_C);
    }
};

#endif