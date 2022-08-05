#include <iostream>
#include <windows.h>
#include <conio.h>

#ifndef UTIL_H
#define UTIL_H
// Pressing these keys makes the position on the board move
#define KEY_UP 72    // arrow up key
#define KEY_DOWN 80  // arrow down key
#define KEY_LEFT 75  // arrow left key
#define KEY_RIGHT 77 // arrow right key

// Pressing this button means the player has decided where to set or shoot
#define FINISHED 13 // enter button.

// Ship placement descriptions
#define SHIPSET 2
#define VALID 1
#define NOTVALID 0

// Colors for ships during ship placement
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
#define VALID_PLACE 2
#define FIXED_PLACE 1
#define INVALID_PLACE 4
#define EMPTY 7

void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#endif