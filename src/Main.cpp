#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Board.h"
#include "./Graphics.h"


int main(int argc, char* args[]){

  // game class responsible for game loop and rendering etc
  Game *game = new Game();
  game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  // GAME LOOP
  while(game->IsRunning()){
    game->ProcessInput();
    game->ProcessAI();
    game->Update();
    game->Render();
  }

  game->Destroy();

  return 0;
}
