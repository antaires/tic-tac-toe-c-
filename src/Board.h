#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"
#include <iostream>

class Board {
private:
  char board[ROW * COLUMN];
  unsigned int moveCount;
  char winner;
  void UpdateBoardState();
  void Test();
  void TestInit();

public:
  Board();
  unsigned int boardState;
  void Initialize();
  bool Update(char piece, unsigned int index);
  void Playing();
  bool GameOver();
  void SetEmpty(unsigned int index);
  unsigned int GetBoardState() const;
  char GetCell(unsigned int index) const;
  void Reset();
};

#endif
