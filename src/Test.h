#ifndef TEST_H
#define TEST_H

#include "./Board.h";
#include "./Game.h";
#include "./Minimax.h";
#include <assert.h>

// blackbox testing of classes

class Test {
private:
  void TestBoard();
  void TestGame();
public:
  Test();
  void RunTests();
};

#endif
