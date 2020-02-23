#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "./Board.h"
#include "./Test.h"

int main(int argc, char* args[]){

  if (TEST){
    Test *test = new Test();
    test->RunTests();
    delete test;
  } 

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
  delete game;

  return 0;
}
