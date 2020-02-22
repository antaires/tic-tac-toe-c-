#include "./Board.h"

unsigned int Board::gameState;

Board::Board(){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      this->board[i][j] = 'E';
    }
  }
  gameState = PLAYING;
  moveCount = 0;
  winner = 'E';
}

Board::~Board(){}

bool Board::Update(char piece, unsigned int row, unsigned int column){
  if (row > (ROW - 1) || column > (COLUMN - 1)){
    return false;
  }
  if (this->board[row][column] == 'E'){
    this->board[row][column] = piece;
    moveCount++;
    this->SetGameState();
    return true;
  }
  return false;
}

void Board::SetGameState(){
  for(int i = 0; i < ROW; ++i){
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2]){
      winner = board[i][0];
    } else if (board[0][i] == board[1][i] && board[1][i] == board[2][i]){
      winner = board[0][i];
    }
  }

  if (winner == 'E' && ((board[0][0] == board[1][1] && board[1][1] == board[2][2])
      || (board[0][2] == board[1][1] && board[1][1] == board[2][0]))){
    winner = board[1][1];
  }

  switch(winner){
    case 'X':
      gameState = X_WIN;
      break;
    case 'O':
      gameState = O_WIN;
      break;
    default:
      gameState = PLAYING;
  }

  if (gameState == PLAYING && moveCount == ROW * COLUMN){
    gameState = DRAW;
    return;
  }
}

unsigned int Board::GetGameState(){
  return gameState;
}

char Board::GetCell(unsigned int row,unsigned int column){
  return this->board[row][column];
}

void Board::GetEmptyCell(unsigned int& row, unsigned int& column){
  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      if (this->board[i][j] == 'E'){
        row = i;
        column = j;
      }
    }
  }
}

bool Board::GameOver(){
  if (gameState == X_WIN || gameState == O_WIN || gameState == DRAW){
    return true;
  }
  return false;
}

bool Board::XWin(){
  if (gameState == X_WIN){
    return true;
  }
  return false;
}

bool Board::OWin(){
  if (gameState == O_WIN){
    return true;
  }
  return false;
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
  // todo
}
