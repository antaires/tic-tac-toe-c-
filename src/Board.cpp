#include "./Board.h"

Board::Board(){}

void Board::Initialize(){
  for (unsigned int i = 0; i < (ROW * COLUMN); ++i){
    this->board[i] = 'E';
  }
  winner = 'E';
  boardState = START;
}

bool Board::Update(char piece, unsigned int index){
  if (index >= (ROW * COLUMN) || this->boardState != PLAYING){
    return false;
  }
  if (this->board[index] == 'E'){
    this->board[index] = piece;
    this->UpdateBoardState();
    return true;
  }
  return false;
}

void Board::UpdateBoardState(){
  if (boardState != PLAYING){
    return;
  }

  if ( board[0] != 'E' &&
      ((board[0] == board[1] && board[1] == board[2]) ||
       (board[0] == board[3] && board[3] == board[6]) ||
       (board[0] == board[4] && board[4] == board[8])) ){
    winner = board[0];
  } else if (
        board[4] != 'E' &&
      ((board[3] == board[4] && board[4] == board[5]) ||
       (board[1] == board[4] && board[4] == board[7]) ||
       (board[6] == board[4] && board[4] == board[2])) ){
    winner = board[4];
  } else if (
       board[8] != 'E' &&
      ((board[6] == board[7] && board[7] == board[8]) ||
      (board[2] == board[5] && board[5] == board[8]))){
    winner = board[8];
  }

  switch(winner){
    case 'X':
      boardState = X_WIN;
      break;
    case 'O':
      boardState = O_WIN;
      break;
    default:
      boardState = PLAYING;
  }

  if (boardState == PLAYING && Board::IsFull()){
    boardState = DRAW;
    return;
  }
}

bool Board::IsFull(){
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    if (board[i] == 'E'){
      return false;
    }
  }
  return true;
}

unsigned int Board::GetBoardState() const {
  return boardState;
}

char Board::GetCell(unsigned int index) {
  return this->board[index];
}

void Board::UndoMove(unsigned int index){
  this->board[index] = 'E';
}

bool Board::SetAll(char cells[]){
  // function for testing states
  if (cells == NULL){return false;}
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    board[i] = cells[i];
  }
  return true;
}

bool Board::GameOver(){
  if (boardState == X_WIN || boardState == O_WIN || boardState == DRAW){
    return true;
  }
  return false;
}

void Board::Playing(){
  boardState = PLAYING;
}

void Board::Reset(){
  boardState = RESET;
}


void Board::Print(){
  std::cout<<"\n";
  for (unsigned int i = 0; i < (ROW * COLUMN); ++i){
    std::cout<<this->board[i];
    if(i == 2 || i == 5){
      std::cout<<"\n";
    }
  }
  std::cout<<"\n";
}
