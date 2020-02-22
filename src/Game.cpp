#include <iostream>
#include "./Constants.h"
#include "./Game.h"
// #include "../lib/glm/glm.hpp" todo needed? if not, remove library

SDL_Renderer* Game::renderer;
SDL_Event Game::event;

// track move
unsigned int currentPlayer;
unsigned char currentMove;
unsigned int row;
unsigned int column;

// todo temporary AI
int rand(void);

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr<< "Error Initializing SDL" << std::endl;
    return;
  }
  window = SDL_CreateWindow(
    NULL
    , SDL_WINDOWPOS_CENTERED
    , SDL_WINDOWPOS_CENTERED
    , width
    , height
    , SDL_WINDOW_BORDERLESS
  );
  if (!window){
    std::cerr<<"Error Creating SDL Window" << std::endl;
    return;
  }
  renderer = SDL_CreateRenderer(window, -1 , 0);
  if (!renderer){
    std::cerr<<"Error Creating SDL Renderer" << std::endl;
    return;
  }
  Start();
  isRunning = true;
  return;
}

void Game::Start(){
  this->board = new Board();
  // todo later, choose who starts (x always 1st)
  this->currentPlayer = HUMAN;
  this->currentMove = 'X';
}

void Game::ProcessInput(){
  SDL_PollEvent(&event);
  switch(event.type){
    case SDL_QUIT: { // clicking 'x button' on window
      isRunning = false;
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        isRunning = false;
      }
    }
    case SDL_MOUSEMOTION: {
      // todo if mouse hovering over square, reduce its alpha
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (currentPlayer == HUMAN){
        int x, y;
        SDL_GetMouseState(&x, &y);
        // get index of clicked cell
        column = std::floor(x / (WINDOW_WIDTH / ROW));
        row = std::floor(y / (WINDOW_HEIGHT / COLUMN));
      }
    }
    default: {
      break;
    }
  }

}

void Game::ProcessAI(){
  // todo update AI
  if (currentPlayer == PC){
    board->GetEmptyCell(row, column);
  }
}

void Game::Update(){
  // make move
  if (board->Update(currentMove, row, column)){
    Game::TogglePlayer();
  }

}

void Game::Render(){
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

  // clear back buffer
  SDL_RenderClear(renderer);

  if (board->GameOver()){
    // todo place in graphics
    if (board->GameOver()){
      if (board->XWin()){
        std::cout<<"\nX wins!";
      } else if (board->OWin()){
        std::cout<<"\nO wins!";
      } else {
        std::cout<<"\nits a draw :/";
      }
    }
    this->isRunning = false;
    return;
  }

  Game::RenderBoard();

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Game::RenderBoard(){
  char cell;
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int h = WINDOW_HEIGHT / ROW;
  unsigned int w = WINDOW_WIDTH / COLUMN;
  for (int i = 0; i < ROW; ++i){
    x = 0;
    for(int j = 0; j < COLUMN; ++j){
      cell = board->GetCell(i, j);
      Game::RenderCell(cell, x, y, w, h);
      x += w;
    }
    y += h;
  }
}

void Game::RenderCell(char cell, int x, int y, int w, int h){
  unsigned int r;
  unsigned int g;
  unsigned int b;

  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;

  switch(cell){
    case 'X':
      r = 52;
      g = 235;
      b = 219;
      break;
    case 'O':
      r = 235;
      g = 171;
      b = 52;
      break;
    default:
      r = 84;
      g = 84;
      b = 84;
  }

  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
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

void Game::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  board->Destroy();
}
