#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Board.h"

class Game {
  private:
    bool isRunning;
    SDL_Window *window;
    void RenderBoard();
  public:
    Game();
    ~Game();
    int ticksLastFrame;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    Board *board;
    static SDL_Event event;
    void LoadLevel(int levelNumber);
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
