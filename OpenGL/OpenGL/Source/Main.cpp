#include "Game/GameManager.h"
#include "Factories/GameScreenFactory.h"


using namespace CelesteEngine;


// The MAIN function, from here we start the application and run the game loop
int main()
{
  GameManager::init();

  Game::transitionToSplashScreen();

  GameManager::run();

  return 0;
}