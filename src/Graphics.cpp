#include "./Graphics.h"

SDL_Renderer* Graphics::renderer;
SDL_Event Graphics::event;
SDL_Window* window;

Graphics::Graphics(){}

Graphics::~Graphics(){}

void Graphics::Initialize(int width, int height){
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
}

bool Graphics::ProcessInput(Board* board, unsigned int currentPlayer, bool isRunning, unsigned int& row, unsigned int& column){
  SDL_PollEvent(&event);
  switch(event.type){
    case SDL_QUIT: { // clicking 'x button' on window
      return false;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        return false;
      }

      // control game state from user input
      if (event.key.keysym.sym == SDLK_RETURN){
        switch(board->GetGameState()){
          case START:
            board->Playing();
            break;
          case PLAYING:
            break;
          default:
            board->Reset();
            break;
        }
      }

    }
    case SDL_MOUSEMOTION: {
      // todo if mouse hovering over square, reduce its alpha
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
        if (board->gameState == PLAYING){
          if (currentPlayer == HUMAN){
            int x, y;
            SDL_GetMouseState(&x, &y);
            // get index of clicked cell
            column = std::floor(x / (WINDOW_WIDTH / ROW));
            row = std::floor(y / (WINDOW_HEIGHT / COLUMN));
          }
      }
      break;
    }
    default: {
      break;
    }
  }
  return true;
}

void Graphics::Render(Board* board){
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  // clear back buffer
  SDL_RenderClear(renderer);

  // todo switch(gameState) to draw different screens!
  switch(board->GetGameState()){
    case START:
      Graphics::RenderStartScreen();
      break;
    case PLAYING:
      Graphics::RenderBoard(board);
      break;
    case X_WIN: // todo create render funcs for different screens, with buttons
      Graphics::RenderEndScreen("X");
      break;
    case O_WIN:
      Graphics::RenderEndScreen("O");
      break;
    case DRAW:
      Graphics::RenderEndScreen("E");
      break;
    default:
      break;
  }

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Graphics::RenderStartScreen(){
  // todo load fonts
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 50, 168,82, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::RenderBoard(Board* board){
  char cell;
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int h = WINDOW_HEIGHT / ROW;
  unsigned int w = WINDOW_WIDTH / COLUMN;
  for (int i = 0; i < ROW; ++i){
    x = 0;
    for(int j = 0; j < COLUMN; ++j){
      cell = board->GetCell(i, j);
      Graphics::RenderCell(cell, x, y, w, h);
      x += w;
    }
    y += h;
  }
}

void Graphics::RenderCell(char cell, int x, int y, int w, int h){
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

void Graphics::RenderEndScreen(std::string outcome){
  // todo
  // todo load fonts
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 158, 16,82, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
