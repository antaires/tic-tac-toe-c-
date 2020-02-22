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
  bool Update(char piece, unsigned int row, unsigned int column);
  char GetCell(unsigned int row, unsigned int column);
  void GetEmptyCell(unsigned int& row, unsigned int& column);
  void Destroy();
};

#endif
