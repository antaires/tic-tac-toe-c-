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
  bool Update(char piece, int row, int column);
  char GetCell(int row, int column);
  void GetEmptyCell(int& row, int& column);
  void Destroy();
};

#endif
