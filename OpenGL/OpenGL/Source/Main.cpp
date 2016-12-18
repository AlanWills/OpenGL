#include "Game/GameManager.h"
#include "Screens/ScreenManager.h"
#include "Time/Clock.h"

#include <thread>
#include <chrono>

using namespace OpenGL;


// The MAIN function, from here we start the application and run the game loop
int main()
{
  GameManager::init();

  ScreenManager* screenManager = GameManager::getScreenManager();
  screenManager->transitionToScreen(screenManager->allocateScreen());

  GameManager::run();

  return 0;
}