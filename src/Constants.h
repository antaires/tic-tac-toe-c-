#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 300;
const unsigned int WINDOW_HEIGHT = 300;

const unsigned int ROW = 3;
const unsigned int COLUMN = 3;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

// players
const unsigned int HUMAN = 0;
const unsigned int PC = 1;

// board state
const unsigned int PLAYING = 0;
const unsigned int X_WIN = 1;
const unsigned int O_WIN = 2;
const unsigned int DRAW = 3;

#endif
