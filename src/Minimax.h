#ifndef MINIMAX_H
#define MINIMAX_H

#include "./Board.h"

class Minimax {
  private:
    int Evaluate(Board* board);
    int MinSearch(Board* clone);
    int MaxSearch(Board* clone);
  public:
    Minimax();
    void GetBestMove(Board* board, unsigned int& index);
    void Clone(Board* original, Board* clone);
};

#endif
