#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"
#include <iostream>

class Board {
private:
  char board[ROW][COLUMN];
  unsigned int moveCount;
  void SetGameState();
  char winner;
  void Print();

public:
  Board();
  ~Board();
  static unsigned int gameState;
  bool GameOver();
  bool XWin();
  bool OWin();
  unsigned int GetGameState();
  bool Update(char piece, unsigned int row, unsigned int column);
  char GetCell(unsigned int row, unsigned int column);
  void GetEmptyCell(unsigned int& row, unsigned int& column);
  void Destroy();
};

#endif
