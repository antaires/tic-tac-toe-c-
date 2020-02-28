#include "./Minimax.h"

/* Takes in a board object and return the best move for the PC
  player using the minimax algorithm.  */

Minimax::Minimax(){}

void Minimax::GetBestMove(Board* board, unsigned int& index){
  // works through each move and scores based on HUMAN or PC winner or DRAW
  Board* clone = new Board();
  Minimax::Clone(board, clone);
  int score = std::numeric_limits<int>::max();
  int move;

  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    if (clone->GetCell(i) == 'E'){
      clone->Playing();
      clone->Update('O', i);
      int temp = MaxSearch(clone);
      if (temp < score){
        score = temp;
        move = i;
      }
      clone->UndoMove(i);
    }
  }
  index = move;
  delete clone;
}

int Minimax::MaxSearch(Board* clone){
  if (clone->GameOver()){
    return Minimax::Evaluate(clone);
  }

  Board* maxClone = new Board();
  int score = std::numeric_limits<int>::min();
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    if (clone->GetCell(i) == 'E'){
      clone->Playing();
      clone->Update('X', i);
      Minimax::Clone(clone, maxClone);
      score = std::max(score, MinSearch(maxClone));
      clone->UndoMove(i);
    }
  }
  delete maxClone;
  return score;
}

int Minimax::MinSearch(Board* clone){
  if (clone->GameOver()){
    return Minimax::Evaluate(clone);
  }
  Board* minClone = new Board();
  int score = std::numeric_limits<int>::max();
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    if (clone->GetCell(i) == 'E'){
      clone->Playing();
      clone->Update('O', i);
      Minimax::Clone(clone, minClone);
      score = std::min(score, MaxSearch(minClone));
      clone->UndoMove(i);
    }
  }
  delete minClone;
  return score;
}

int Minimax::Evaluate(Board* cloneBoard){
  // determines point value of initial move based on game outcome
  switch (cloneBoard->GetBoardState()){
    case X_WIN:
      // winner is maximizer (HUMAN)
      return (WINPOINTS);
    case O_WIN:
      // winner is minimizer (PC)
      return (LOSEPOINTS);
    default:
      return 0;
  }
}

void Minimax::Clone(Board* original, Board* clone){
  clone->Initialize();
  clone->Playing();
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    clone->Update(original->GetCell(i), i);
  }
}
