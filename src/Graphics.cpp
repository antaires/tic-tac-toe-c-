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

  // init SDL_ttf
  if (TTF_Init() != 0){
    std::cerr<<"Error Initializing TTF" <<std::endl;
    return;
  }
  font = LoadFont();
}

bool Graphics::ProcessInput(Board* board, unsigned int gameState, unsigned int currentPlayer, bool isRunning, unsigned int& row, unsigned int& column){
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
        switch(gameState){
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
        if (gameState == PLAYING){
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

void Graphics::Render(Board* board, unsigned int gameState){
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  // clear back buffer
  SDL_RenderClear(renderer);

  switch(gameState){
    case START:
      Graphics::RenderStartScreen();
      break;
    case PLAYING:
      Graphics::RenderBoard(board);
      break;
    case X_WIN:
    case O_WIN:
    case DRAW:
      Graphics::RenderEndScreen(board, gameState);
      break;
    default:
      break;
  }

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Graphics::RenderStartScreen(){
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  SDL_RenderFillRect(renderer, &rect);
  Graphics::RenderText(std::string("Tic").c_str(), WINDOW_WIDTH / 3, 0);
  Graphics::RenderText(std::string("Tac").c_str(), WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);
  Graphics::RenderText(std::string("Toe").c_str(), WINDOW_WIDTH / 3, (WINDOW_HEIGHT / 3) *2);
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
  Graphics::RenderLines();
}

void Graphics::RenderCell(char cell, int x, int y, int w, int h){
  unsigned int r;
  unsigned int g;
  unsigned int b;
  std::string text;

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
      text = "X";
      break;
    case 'O':
      r = 235;
      g = 171;
      b = 52;
      text = "O";
      break;
    default:
      r = 84;
      g = 84;
      b = 84;
      text = "";
  }

  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
  Graphics::RenderText(text.c_str(), (x + X_OFFSET), (y + Y_OFFSET));
}

void Graphics::RenderLines(){
  Graphics::RenderLine(WINDOW_WIDTH / 3, 0, 10, WINDOW_HEIGHT);
  Graphics::RenderLine((WINDOW_WIDTH / 3 )* 2, 0, 10, WINDOW_HEIGHT);
  Graphics::RenderLine(0, WINDOW_HEIGHT /3, WINDOW_WIDTH, 10);
  Graphics::RenderLine(0, (WINDOW_HEIGHT / 3 )* 2, WINDOW_WIDTH, 10);
}

void Graphics::RenderLine(int x, int y, int w, int h){
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void Graphics::RenderText(const char* text, int x, int y){
  if (!text || !font){
    std::cerr<<"\nCannot render text";
    return;
  }
  int textW = 0;
  int textH = 0;
  SDL_Color White = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
  SDL_QueryTexture(Message, NULL, NULL, &textW, &textH);
  SDL_Rect pos;
  pos.x = x;
  pos.y = y;
  pos.w = textW;
  pos.h = textH;
  SDL_RenderCopy(renderer, Message, NULL, &pos);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}


TTF_Font* Graphics::LoadFont(){
  TTF_Font* f = TTF_OpenFont(std::string("./assets/fonts/arial.ttf").c_str(), 100);
  if (!f){
    std::cout<<TTF_GetError();
    std::cerr<<"\nCannot load font";
  }
  return f;
}

void Graphics::RenderEndScreen(Board* board, unsigned int gameState){
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = WINDOW_WIDTH;
  rect.h = WINDOW_HEIGHT;
  SDL_SetRenderDrawColor(renderer, 65, 112, 100, 255);
  SDL_RenderFillRect(renderer, &rect);

  switch(gameState){
    case X_WIN:
      Graphics::RenderText(std::string(" X").c_str(), WINDOW_WIDTH / 3, 0);
      Graphics::RenderText(std::string("Wins").c_str(), WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);
      break;
    case O_WIN:
    Graphics::RenderText(std::string(" O").c_str(), WINDOW_WIDTH / 3, 0);
    Graphics::RenderText(std::string("Wins").c_str(), WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);
      break;
    default:
    Graphics::RenderText(std::string("Draw").c_str(), WINDOW_WIDTH / 4, WINDOW_HEIGHT / 3);
      break;
  }
}

void Graphics::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}
