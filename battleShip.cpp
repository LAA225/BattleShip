#include "player.cpp"
#include <iostream>
#include <string>

using namespace std;

#ifndef BATTLESHIP_CPP
#define BATTLESHIP_CPP

class BattleShip
{
     Player *player1;
     Player *player2;

     void firstscreen()
     {
          system("COLOR 3F");
          cout << "\n\n\n\n\n";
          cout << "        ___            _____  _____         ____   __            __  \n"
               << "       |   \\    /\\       |      |    |     |      /  \\ |   |  | |  \\ \n"
               << "       |___/   /__\\      |      |    |     |____  \\__  |___|  | |__/  \n"
               << "       |   \\  /    \\     |      |    |     |         \\ |   |  | |    \n"
               << "       |___/ /      \\    |      |    |____ |____  \\__/ |   |  | |    \n";

          cout << "\n\n"
               << "                              Version 1.0\n"
               << "                             By Laiba Abid \n\n"
               << "                               Loading";

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
     void rules()
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
               << "Ships can be placed by using the arrow keys to view all possibilities across the board" << endl
               << "You can change orientation by clicking the Space bar" << endl
               << "Press Enter to place the ship." << endl
               << "Once the ship has been placed, the players may not move the ships." << endl 
               << endl
               << "The 5 ships are: Aircraft Carrier (occupies 5 spaces in the shape of a T)," << endl
               << "Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2)." << endl
               << endl;
          cout << "SHOOTING:" << endl
               << "Each player will try and hit the opponent's ship by selecting" << endl
               << "the coordinates of one of the squares on the board by using the arrow keys and Enter." << endl
               << "If a player hits his opponent's ship," << endl
               << "a hit is declared by a red 'X' on the grid. " << endl
               << "A miss is marked with a blue 'X'" << endl
               << "If it is a hit, the player gets another turn otherwise the turn is" << endl
               << "passed on to the other player." << endl
               << "The game ends when all the ships of one player have been sunk." << endl
               << endl
               << endl;

          waitForUser();
     }
     void win(Player *winner)
     {
          Sleep(1000);
          system("CLS");
          system("COLOR 3F");
          cout << endl
               << endl
               << endl
               << endl
               << "                        "
               << winner->getName() << " has won the game!!"
               << endl
               << endl;
          // PlaySound(TEXT("Win1.wav"), NULL, SND_SYNC);
          Sleep(1000);
          system("COLOR 07");
          return;
     }
     bool ShipsFinished(Player *p)
     {
          if (p->shipPartsRemaining() == 0)
          {
               return true;
          }

          return false;
     }
     void swapPlayers(Player *&a, Player *&b)
     {
          Player *temp = a;
          a = b;
          b = temp;
     }
     void battle()
     {
          Player *attackPlayer = player1;
          Player *defensePlayer = player2;
          bool endGame = false;
          bool hit = false;
          string msg = attackPlayer->getName() + " gets to shoot first.";

          while (!endGame)
          {
               hit = attackPlayer->shoot(defensePlayer, msg);
               if (hit)
               {
                    if (ShipsFinished(defensePlayer))
                    {
                         win(attackPlayer);
                         endGame = true;
                    }
                    else{
                         msg = "Hit! " + attackPlayer->getName() + " gets another turn for hitting \n";
                    }
               }
               else // miss
               {
                    msg = "Miss. " + defensePlayer->getName() + "'s turn to shoot. \n";
                    swapPlayers(attackPlayer, defensePlayer);
               }
          }
     }

public:
     BattleShip()
     {
          firstscreen();
          rules();

          // setup players
          player1 = new Player();
          player2 = new Player();

          // set names
          string x;
          cout << "Enter player 1's name: ";
          cin >> x;
          player1->setName(x);

          cout << "Enter player 2's name: ";
          cin >> x;
          player2->setName(x);

          // setup ships
          cout << "First player 1 gets to set their ships. \n";
          player1->setupShips();
          cout << "Now player 2 gets to set their ships. \n";
          player2->setupShips();

          // game begin
          battle();
     }
};

#endif