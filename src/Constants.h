#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <assert.h>

// window
const unsigned int WINDOW_WIDTH = 300;
const unsigned int WINDOW_HEIGHT = 300;

// board
const unsigned int ROW = 3;
const unsigned int COLUMN = 3;
const unsigned int X_OFFSET = 20;
const unsigned int Y_OFFSET = 0;

// players
const unsigned int HUMAN = 0;
const unsigned int PC = 1;

// board state
const unsigned int PLAYING = 0;
const unsigned int X_WIN = 1;
const unsigned int O_WIN = 2;
const unsigned int DRAW = 3;
const unsigned int START = 4;
const unsigned int RESET = 5;

// Minimax
const int WINPOINTS = 10;
const int LOSEPOINTS = -10;
const char MAXIMIZER = 'X';
const char MINIMIZER = 'O';

// testing
const bool TEST = false;

#endif
