#include "./Game.h"

Game::Game() {
  this->isRunning = false;
}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  this->board = new Board();
  this->graphics = new Graphics();
  this->minimax = new Minimax();
  graphics->Initialize(width, height);
  Start();
  isRunning = true;
  return;
}

void Game::Start(){
  this->currentPlayer = HUMAN;
  this->currentMove = 'X';
  this->index = (ROW * COLUMN);
  gameState = START;
  board->Initialize();
}

void Game::ProcessInput(){
  if (!graphics->ProcessInput(board, gameState, currentPlayer, isRunning, index)){
    isRunning = false;
  }
  if (board->GetBoardState() == RESET){
    Game::Start();
  }
}

void Game::ProcessAI(){
  if (currentPlayer == PC && gameState == PLAYING){
    minimax->GetBestMove(board, index);
  }
}

void Game::Update(){
  // set move on board
  if (board->Update(currentMove, index)){
    Game::TogglePlayer();
  }
  gameState = board->GetBoardState();
}

void Game::Render(){
  graphics->Render(board, gameState);
}

void Game::TogglePlayer(){
  if (currentPlayer == HUMAN){
    currentPlayer = PC;
    currentMove = 'O';
  } else {
    currentPlayer = HUMAN;
    currentMove = 'X';
  }
}

unsigned int Game::GetGameState(){
  return board->GetBoardState();
}

unsigned int Game::GetCurrentPlayer(){
  return this->currentPlayer;
}
unsigned int Game::GetCurrentMove(){
  return this->currentMove;
}
unsigned int Game::GetIndex(){
  return this->index;
}

void Game::Destroy(){
  graphics->Destroy();
  delete board;
  delete graphics;
  delete minimax;
}
