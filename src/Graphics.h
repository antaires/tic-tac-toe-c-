#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Board.h"
#include <cmath>
#include <cstdlib>

class Graphics {
  private:
    void RenderStartScreen();
    void RenderBoard(Board* board);
    void RenderCell(char cell, int x, int y, int w, int h);
    void RenderEndScreen(std::string outcome);
  public:
    Graphics();
    ~Graphics();
    static SDL_Renderer *renderer;
    static SDL_Event event;
    SDL_Window *window;

    void Initialize(int width, int height);
    bool ProcessInput(Board* board, unsigned int currentPlayer, bool isRunning, unsigned int& row, unsigned int& column);
    void Update();
    void Render(Board* board);
    void Destroy();
};

#endif
