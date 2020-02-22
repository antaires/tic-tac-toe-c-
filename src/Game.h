#ifndef GAME_H
#define GAME_H

#include "./Graphics.h"

class Game {
  private:
    bool isRunning;
    unsigned int currentPlayer;
    unsigned int currentMove;
    unsigned int row;
    unsigned int column;
    void TogglePlayer();

  public:
    Game();
    ~Game();
    bool IsRunning() const;
    static Board *board;
    Graphics* graphics;

    void Start();
    void Initialize(int width, int height);
    void ProcessInput();
    void ProcessAI();
    void Update();
    void Render();
    void Destroy();
};

#endif
