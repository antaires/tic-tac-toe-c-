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
const unsigned int START = 0;
const unsigned int HUMAN_TURN = 1;
const unsigned int PC_TURN = 2;
const unsigned int HUMAN_WIN = 3;
const unsigned int PC_WIN = 4;
const unsigned int DRAW = 5;

#endif
