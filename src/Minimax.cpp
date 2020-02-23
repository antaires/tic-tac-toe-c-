#include "./Minimax.h"

/* Takes in a board object and return the best move for the PC
  player using the minimax algorithm. A variation is unsigned
  to preference moves that lead to quick wins or slow losses */

Minimax::Minimax(){}

void Minimax::GetBestMove(Board* board, unsigned int& row, unsigned int& column){
  // works through each move and scores based on HUMAN or PC winner or DRAW
  unsigned int bestMoveRow = 0;
  unsigned int bestMoveCol = 0;
  int currentMove = 0;
  int bestMoveValue = -1;
  bool isMaximizingPlayer = false; // always false in this implementation
  Board* cloneBoard = new Board();
  Minimax::Clone(board, cloneBoard);
  // if board empty, pick random start (PC always goes 2nd, so can skip)
  
  // get each empty square
  for(int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      if (cloneBoard->GetCell(i, j) == 'E'){
        cloneBoard->Update('O', i, j); // need to update this to always be PC if player can choose X or O
        currentMove = Minimax::MinimaxCalc(cloneBoard, 0, true); // PC always minimizing (todo should this be false)
        // undo move
        cloneBoard->SetEmpty(i, j);

        // if maximizer (skip - PC always minimizing)
        if (isMaximizingPlayer){
          if (currentMove > bestMoveValue){
            bestMoveValue = currentMove;
            bestMoveRow = i;
            bestMoveCol = j;
          }
        } else {
          // if MINIMIZER
          if (currentMove < bestMoveValue){
            bestMoveValue = currentMove;
            bestMoveRow = i;
            bestMoveCol = j;
          }
        }
      }
    }
  }
  // set best move
  row = bestMoveRow;
  column = bestMoveCol;
}

int Minimax::Evaluate(Board* cloneBoard, int depth){
  // determines point value of initial move based on game outcome
  // depth is number of moves made prior to game end state
  switch (cloneBoard->GetBoardState()){
    case X_WIN:
      // winner is maximizer (HUMAN)
      return (WINPOINTS - depth);
    case O_WIN:
      // winner is minimizer (PC)
      return (LOSEPOINTS + depth);
    default:
      return 0;
  }
}

int Minimax::MinimaxCalc(Board* cloneBoard, int depth, bool isMaximizingPlayer){
  // Minimax: https://en.wikipedia.org/wiki/Minimax
  unsigned int state = cloneBoard->GetBoardState();
  if (state == X_WIN || state == O_WIN || state == DRAW){
    return Minimax::Evaluate(cloneBoard, depth);
  }

  int bestValue;
  Board* clone = new Board();
  Minimax::Clone(cloneBoard, clone);

  if (isMaximizingPlayer){
    // maximizer
    bestValue = -10000;
    for(int i = 0; i < ROW; ++i){
      for(int j = 0; j < COLUMN; ++j){
        if (clone->GetCell(i, j) == 'E'){
          clone->Update('X', i, j);
          int value = Minimax::MinimaxCalc(clone, depth+1, false);
          bestValue = bestValue > value ? bestValue : value;
          clone->SetEmpty(i, j);
        }
      }
    }
    return bestValue;
  } else {
    // minimizer
    int bestValue = 10000;
    for(int i = 0; i < ROW; ++i){
      for(int j = 0; j < COLUMN; ++j){
        if (clone->GetCell(i, j) == 'E'){
          clone->Update('O', i, j);
          int value = Minimax::MinimaxCalc(clone, depth+1, true);
          bestValue = bestValue < value ? bestValue : value;
          clone->SetEmpty(i, j);
        }
      }
    }
  }
  return bestValue;
}

void Minimax::Clone(Board* original, Board* clone){
  for(int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      clone->Update(original->GetCell(i, j), i, j);
    }
  }
}
