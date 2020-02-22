#include <iostream>
#include "./Constants.h"
#include "./Game.h"
// #include "../lib/glm/glm.hpp" todo needed? if not, remove library

SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  // create all SDL inits / flow
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

  LoadLevel(0);

  isRunning = true;
  return;
}

void Game::LoadLevel(int levelNumber){
  board = new Board();
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
    default: {
      break;
    }
  }
}

void Game::Update(){
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  // delta time is difference in ticks from last frame converted to seconds
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  // clamp to max value - set max deltaTime, in case of debugging or delay
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  // sets the new ticks for the current frame to be used in the next pass
  ticksLastFrame = SDL_GetTicks();

  board->Update(deltaTime);

}

void Game::Render(){
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

  // clear back buffer
  SDL_RenderClear(renderer);

  if (board->GameOver()){
    return;
  }

  Game::RenderBoard();

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Game::RenderBoard(){
  // todo
  // draw each cell to screen
  // use texture Managager
  // to start, just draw diff colored rectangles (black = E, red = X, blue = 0)
  char cell;
  int x = 0;
  int y = 0;
  int h = WINDOW_HEIGHT / 3; // todo int/float any issues for diff sizes?
  int w = WINDOW_WIDTH / 3;

  unsigned int r;
  unsigned int g;
  unsigned int b;

  for (int i = 0; i < ROW; ++i){
    for(int j = 0; j < COLUMN; ++j){
      cell = board->GetCell(i, j);
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

      // increment positions x y
      x += w;
      y += h;
    }
  }
}

void Game::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
