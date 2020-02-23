#include "./Minimax.h"

/* Takes in a board object and return the best move for the PC
  player using the minimax algorithm. This variation
  preferences moves that lead to quick wins or slow losses */

Minimax::Minimax(){}

void Minimax::GetBestMove(Board* board, unsigned int& index){
  // works through each move and scores based on HUMAN or PC winner or DRAW
  unsigned int bestMove = 0;
  int bestMoveValue = 10000;
  bool isMaximizingPlayer = false; // always false in this implementation
  Board* cloneBoard = new Board();
  Minimax::Clone(board, cloneBoard);
  currentMove = -1;

  // get each empty square
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    if (cloneBoard->GetCell(i) == 'E'){

      cloneBoard->Update('O', i);
      Minimax::MinimaxCalc(cloneBoard, 0, true, currentMove);
      // undo move
      cloneBoard->SetEmpty(i);
      // if MINIMIZER
      if (currentMove < bestMoveValue){
        bestMoveValue = currentMove;
        bestMove = i;
      }
    }
  }
  index = bestMove;
  delete cloneBoard;
}

void Minimax::Evaluate(Board* cloneBoard, int depth){
  // determines point value of initial move based on game outcome
  // depth is number of moves made prior to game end state
  switch (cloneBoard->GetBoardState()){
    case X_WIN:
      // winner is maximizer (HUMAN)
      this->currentMove = (WINPOINTS - depth);
    case O_WIN:
      // winner is minimizer (PC)
      this->currentMove = (LOSEPOINTS + depth);
    default:
      this->currentMove = 0;
  }
}

void Minimax::MinimaxCalc(Board* cloneBoard, int depth, bool isMaximizingPlayer, int& returnValue){
  // Minimax: https://en.wikipedia.org/wiki/Minimax
  unsigned int state = cloneBoard->GetBoardState();
  if (state == X_WIN || state == O_WIN || state == DRAW){
    Minimax::Evaluate(cloneBoard, depth);
    return;
  }

  int bestValue;
  Board* clone = new Board();
  Minimax::Clone(cloneBoard, clone);

  if (isMaximizingPlayer){
    // maximizer
    bestValue = -10000;
    for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
      if (clone->GetCell(i) == 'E'){
        clone->Playing();
        clone->Update('X', i);
        int value;
        Minimax::MinimaxCalc(clone, depth+1, false, value);
        bestValue = bestValue > value ? bestValue : value;
        clone->SetEmpty(i);
      }
    }
    delete clone;
    returnValue = bestValue;
    return;
  } else {
    // minimizer
    int bestValue = 10000;
    for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
      if (clone->GetCell(i) == 'E'){
        clone->Update('O', i);
        int value;
        Minimax::MinimaxCalc(clone, depth+1, true, value);
        bestValue = bestValue < value ? bestValue : value;
        clone->SetEmpty(i);
      }
    }
  }
  delete clone;
  returnValue = bestValue;
  return;
}

void Minimax::Clone(Board* original, Board* clone){
  clone->Initialize();
  clone->Playing();
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    clone->Update(original->GetCell(i), i);
  }
}
