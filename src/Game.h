#ifndef GAME_H
#define GAME_H

#include "./Graphics.h"
#include "./Minimax.h"

class Game {
  private:
    bool isRunning;
    unsigned int currentPlayer;
    unsigned int currentMove;
    unsigned int index;
    void TogglePlayer();

  public:
    Game();
    unsigned int gameState;
    Board *board;
    Graphics* graphics;
    Minimax* minimax;
    void Start();
    void Initialize(int width, int height);
    void ProcessInput();
    void ProcessAI();
    void Update();
    void Render();
    void Destroy();
    bool IsRunning() const;
    unsigned int GetGameState();
    unsigned int GetCurrentPlayer();
    unsigned int GetCurrentMove();
    unsigned int GetIndex();
};

#endif
