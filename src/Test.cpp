#include "./Test.h"

Test::Test(){}

void Test::RunTests(){
  Test::TestBoard();
  Test::TestGame();
  Test::TestMinimax();
}

void Test::TestBoard(){

    Board* b = new Board();
    b->Initialize();
    assert(b->GetBoardState() == START);

    // test init
    for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
      assert(b->GetCell(i) == 'E');
    }
    // no update if gamestate not Playing
    assert(b->Update('X', 5) == false);
    assert(b->GetCell(5) == 'E');

    b->Playing();
    assert(b->GetBoardState() == PLAYING);

    // test update
    assert(b->GetCell(4) == 'E');
    assert(b->Update('X', 4) == true);
    assert(b->GetCell(4) == 'X');
    assert(b->Update('O', 8) == true);
    assert(b->GetCell(8) == 'O');
    // once a move made, cannot override it
    assert(b->Update('X', 8) == false);
    assert(b->GetCell(8) == 'O');

    // test win condition
    assert(b->Update('X', 2) == true);
    assert(b->Update('X', 6) == true);
    assert(b->GameOver() == true);
    assert(b->GetBoardState() == X_WIN);

    // RESET
    b->Reset();
    assert(b->GetBoardState() == RESET);
    b->Initialize();
    b->Playing();
    for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
      assert(b->GetCell(i) == 'E');
    }

    // test more win conditions
    assert(b->Update('O', 3) == true);
    assert(b->Update('O', 4) == true);
    assert(b->Update('O', 5) == true);
    assert(b->GameOver() == true);
    assert(b->GetBoardState() == O_WIN);
    b->Reset();
    b->Initialize();
    b->Playing();
    assert(b->Update('O', 0) == true);
    assert(b->Update('X', 1) == true);
    assert(b->Update('O', 2) == true);
    assert(b->Update('X', 3) == true);
    assert(b->Update('O', 4) == true);
    assert(b->Update('X', 5) == true);
    assert(b->Update('X', 6) == true);
    assert(b->Update('O', 7) == true);
    assert(b->Update('X', 8) == true);
    assert(b->GameOver() == true);
    assert(b->GetBoardState() == DRAW);

    // test set empty
    assert(b->GetCell(1) == 'X');
    b->UndoMove(1);
    assert(b->GetCell(1) == 'E');

    delete b;
}

void Test::TestGame(){
  Game* g = new Game();
  assert(g->IsRunning() == false);

  g->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
  assert(g->IsRunning() == true);
  assert(g->GetCurrentPlayer() == HUMAN);
  assert(g->GetCurrentMove() == 'X');
  assert(g->GetIndex() == (ROW * COLUMN));
  assert(g->GetGameState() == START);

  delete g;
}

void Test::TestMinimax(){
  Minimax* m = new Minimax();
  Board* b = new Board();
  b->Initialize();
  b->Playing();
  unsigned int index = 0;

  // test Clone
  Board* clone = new Board();
  char cells0[(ROW * COLUMN)] = {'X', 'X', 'E', 'O', 'E', 'X', 'E', 'E', 'E'};
  b->SetAll(cells0);
  m->Clone(b, clone);
  for(unsigned int i = 0; i < (ROW * COLUMN); ++i){
    assert(clone->GetCell(i) == b->GetCell(i));
  }

  // test scenario (6 is a win for O)
  char cells1[(ROW * COLUMN)] = {'O', 'X', 'E', 'O', 'E', 'X', 'E', 'E', 'E'};
  b->Playing();
  b->SetAll(cells1);
  b->Update('X', 8);
  m->GetBestMove(b, index);
  assert(index == 6);

  delete b;
  delete m;
}
