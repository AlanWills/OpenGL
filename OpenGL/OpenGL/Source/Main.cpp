#include "Game/GameManager.h"
#include "Time/Clock.h"

#include <thread>
#include <chrono>

using namespace OpenGL;


// The MAIN function, from here we start the application and run the game loop
int main()
{
  GameManager::init();
  GameManager::run();

  return 0;
}