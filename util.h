#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;

#ifndef UTIL_H
#define UTIL_H

// Buttons/keys to change position on the board
#define KEY_UP 72    // arrow up key
#define KEY_DOWN 80  // arrow down key
#define KEY_LEFT 75  // arrow left key
#define KEY_RIGHT 77 // arrow right key

// Button/Key to change orientation of ship
#define ORIENTATION 32 // space bar

// Button/key to select a spot
#define FINISHED 13 // enter button.

// Ship placement descriptions
#define VALID 1
#define NOTVALID 0

// symbols for play
#define MISS 'X'
#define HIT 'X'
#define SEARCH 'O'
#define EMPTY '.'

// COLORS LIST
// 1: Blue
// 2: Green
// 3: Cyan
// 4: Red
// 5: Purple
// 6: Yellow (Dark)
// 7: Default white
// 8: Gray/Grey
// 9: Bright blue
// 10: Brigth green
// 11: Bright cyan
// 12: Bright red
// 13: Pink/Magenta
// 14: Yellow
// 15: Bright white

// Colors for ships during ship placement
#define VALID_PLACE_C 2
#define INVALID_PLACE_C 4
#define FIXED_PLACE_C 1
#define EMPTY_C 7

// Colors for during play
#define MISS_C 1
#define HIT_C 4
#define SEARCH_C 14

void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void waitForUser()
{
    cout << "Press Enter to continue.............";
    cin.get();
    system("CLS");
}

#endif