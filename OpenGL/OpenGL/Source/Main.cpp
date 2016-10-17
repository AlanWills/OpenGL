#include "Game.h"
#include "Managers/GameManager.h"
#include "Time/Clock.h"

#include <thread>
#include <chrono>

using namespace Engine;

int main(int argc, char *argv[])
{
  GLFW_INIT();

  GameManager::init();

  GLEW_INIT();

  GameManager::run();

  GLFW_TERMINATE();

  return 0;
}