#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"
#include <iostream>

class Board {
private:
  char board[ROW][COLUMN];
  void Print();
public:
  Board();
  ~Board();
  bool GameOver();
  bool MakeMove();
  bool Update(float deltaTime);
  char GetCell(int row, int column);
  void Destroy();
};

#endif
