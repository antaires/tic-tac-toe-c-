#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"

class Board {
private:
  char board[ROW][COLUMN];
public:
  Board();
  ~Board();
  bool GameOver();
  bool MakeMove();
  bool Update(float deltaTime);
  void Render();
  void Destroy();
};

#endif
