#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Board.h"
#include <cmath>
#include <cstdlib>

class Game {
  private:
    bool isRunning;
    SDL_Window *window;
    unsigned int currentPlayer;
    unsigned int currentMove;
    unsigned int row;
    unsigned int column;
    void RenderBoard();
    void RenderCell(char cell, int x, int y, int w, int h);
    void TogglePlayer();
  public:
    Game();
    ~Game();
    int ticksLastFrame;
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    Board *board;
    static SDL_Event event;
    void Start();
    void Initialize(int width, int height);
    void ProcessInput();
    void ProcessAI();
    void Update();
    void Render();
    void Destroy();
};

#endif
