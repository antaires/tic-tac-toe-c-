#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"
#include <iostream>

class Board {
private:
  char board[ROW][COLUMN];
  unsigned int moveCount;
  void SetBoardState();
  char winner;

public:
  Board();
  ~Board();
  unsigned int boardState;
  bool GameOver();
  unsigned int GetBoardState();
  void Playing();
  bool Update(char piece, unsigned int row, unsigned int column);
  char GetCell(unsigned int row, unsigned int column);
  void GetEmptyCell(unsigned int& row, unsigned int& column);
  void SetEmpty(unsigned int row, unsigned int column);
  void Reset();
  void SetUpBoard();
  void Destroy();
  void Print();
};

#endif
