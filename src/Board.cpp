#include "./Board.h"


Board::Board(){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      board[i][j] = 'E';
    }
  }
}
Board::~Board(){}

bool Board::GameOver(){
  return false;
}

bool Board::MakeMove(){
  return false;
}

bool Board::Update(float deltaTime){
  return false;
}

void Board::Render(){} // todo possibly keep render in game only (board doesn't know about graphics)

void Board::Destroy(){
  // todo free memory from heap
}
