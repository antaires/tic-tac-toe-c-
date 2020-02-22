#include "./Board.h"

char board[ROW][COLUMN];

Board::Board(){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      board[i][j] = 'E';
    }
  }
  // todo remove (JUST FOR TESTING)
  board[0][0] = 'X';
  board[1][1] = 'O';
  board[2][2] = 'X';

  Board::Print();
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

char Board::GetCell(int row, int column){ // todo possibly keep render in game only (board doesn't know about graphics)
  return board[row][column];
}

void Board::Print(){
  // todo remove
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      std::cout<<board[i][j]<<" ";
      if (j == 2){
        std::cout<<"\n";
      }
    }
  }
}

void Board::Destroy(){
  // todo free memory from heap
}
