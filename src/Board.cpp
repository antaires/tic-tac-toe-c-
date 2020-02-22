#include "./Board.h"

char board[ROW][COLUMN];

Board::Board(){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      this->board[i][j] = 'E';
    }
  }
}

Board::~Board(){}

bool Board::GameOver(){
  // todo
  return false;
}

bool Board::Update(char piece, int row, int column){
  if (this->board[row][column] == 'E'){
    this->board[row][column] = piece;
    return true;
  }
  return false;
}

char Board::GetCell(int row, int column){
  return this->board[row][column];
}

void Board::GetEmptyCell(int& row, int& column){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      if (this->board[i][j] == 'E'){
        row = i;
        column = j;
      }
    }
  }
}

void Board::Print(){
  // todo remove
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      std::cout<<this->board[i][j]<<" ";
      if (j == (COLUMN - 1)){
        std::cout<<"\n";
      }
    }
  }
}

void Board::Destroy(){
  // todo free memory from heap
}
