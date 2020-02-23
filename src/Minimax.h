#ifndef MINIMAX_H
#define MINIMAX_H

#include "./Board.h"

class Minimax {
  private:
    int Evaluate(Board* board, int depth);
    int MinimaxCalc(Board* cloneBoard, int depth, bool isMaximizingPlayer);
    void Clone(Board* original, Board* clone);

  public:
    Minimax();
    void GetBestMove(Board* board, unsigned int& row, unsigned int& column);

};

#endif
