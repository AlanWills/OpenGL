#include "SpaceGame.h"


// The MAIN function, from here we start the application and run the game loop
int main()
{
  // Don't need to use unique_ptr as it will be deleted through 'current' unique_ptr
  SpaceGame::SpaceGame* game = new SpaceGame::SpaceGame();
  game->run();

  return 0;
}