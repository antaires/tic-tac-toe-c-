#include "./Game.h"

// #include "../lib/glm/glm.hpp" todo needed(textures)? if not, remove library

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {}

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
  // todo later, choose who starts (x always 1st)
  this->currentPlayer = HUMAN;
  this->currentMove = 'X';
  this->row = ROW;
  this->column = COLUMN;
  board->SetUpBoard();
  gameState = START;
}

void Game::ProcessInput(){
  if (!graphics->ProcessInput(board, gameState, currentPlayer, isRunning, row, column)){
    isRunning = false;
  }
  if (board->GetBoardState() == RESET){
    Game::Start();
  }
}

void Game::ProcessAI(){
  if (currentPlayer == PC && gameState == PLAYING){
    // minimax->GetBestMove(board, row, column);
    board->GetEmptyCell(row, column);
  }
}

void Game::Update(){
  // set move on board
  if (board->Update(currentMove, row, column)){
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

void Game::Destroy(){
  graphics->Destroy();
}
