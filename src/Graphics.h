#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Board.h"
#include <cmath>
#include <cstdlib>
#include <string>

class Graphics {
  private:
    TTF_Font* font;
    void RenderStartScreen() const;
    void RenderBoard(Board* board) const;
    void RenderCell(char cell, int x, int y, int w, int h) const;
    void RenderEndScreen(Board* board, unsigned int gameState) const;
    void RenderText(const char* text, int x, int y) const;
    void RenderLines() const;
    void RenderLine(int x, int y, int w, int h) const;
    unsigned int GetIndex(unsigned int row, unsigned int column) const;
    TTF_Font* LoadFont();
  public:
    Graphics();
    static SDL_Renderer *renderer;
    static SDL_Event event;
    SDL_Window *window;

    void Initialize(int width, int height);
    bool ProcessInput(Board* board, unsigned int gameState, unsigned int currentPlayer, bool isRunning, unsigned int& index);
    void Update();
    void Render(Board* board, unsigned int gameState) const;
    void Destroy();
};

#endif
