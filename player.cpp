#include "board.h"
#include "ship.h"
#include "AircraftCarrier.cpp"
#include <unordered_map>

using namespace std;

class Player
{
    // records ship placement
    Board shipBoard;
    // records moves made by player
    Board movesBoard;

    // an map of symbols to different types of ships and possible ship class derivatives
    unordered_map<char, Ship *> ships;

    // total ship parts remaining to be hit
    int shipParts = 0;

    void setupShips()
    {
        // to add more ordinary ships add to these lists
        vector<string> names = {"BattleShip", "Carrier", "Cruiser", "Destroyer"};
        vector<char> symbols = {'B', 'C', 'S', 'D'};
        vector<int> lengths = {5, 4, 3, 2};

        // special ship
        Ship *temp = new AircraftCarrier();
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
    bool navigate(coordinate point)
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
            case FINISHED:
                return true;
            default:
                break;
            }
        }
    }

    coordinate chooseLocation()
    {
        bool Chosen = false;
        coordinate point(movesBoard.lowerLimit, movesBoard.lowerLimit);
        coordinate prevPoint = point;

        char prevSym = ' ';
        int prevCol = EMPTY;

        while (!Chosen)
        {
            movesBoard.draw(point, SEARCH, SEARCH_C);
            movesBoard.display();
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
        if (sym == '.' || sym == '0') // miss
        {
            return false;
        }
        else // hit
        {
            return true;
        }
    }

public:
    Player()
    {
        setupShips();
    }

    bool shoot(Player &oponent)
    {
        coordinate point = chooseLocation();

        bool conclusion = evaluateHit(point);
        if (conclusion == true)
        {
            movesBoard.draw(point, HIT, HIT_C);
            // evaluate how to know if a ship has been sunk.
            // i.e how to correlate symbol with ship.
            // could make an enum and use that
            // would also help with which ships to add on the util page
        }
        else
        {
            movesBoard.draw(point, MISS, MISS_C);
        }
        movesBoard.display();
        return conclusion;
    }
};