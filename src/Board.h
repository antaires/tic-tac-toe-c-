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
  bool IsFull();

public:
  Board();
  unsigned int boardState;
  void Initialize();
  bool Update(char piece, unsigned int index);
  void Playing();
  bool GameOver();
  void UndoMove(unsigned int index);
  unsigned int GetBoardState() const;
  char GetCell(unsigned int index);
  void Reset();
  bool SetAll(char cells[]);
  void Print();
};

#endif
