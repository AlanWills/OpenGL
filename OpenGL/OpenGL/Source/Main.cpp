#include "Game/GameManager.h"
#include "Factories/GameScreenFactory.h"
#include "Viewport/TopDownCamera.h"


using namespace CelesteEngine;


// The MAIN function, from here we start the application and run the game loop
int main()
{
  GameManager::init();

  TopDownCamera* camera = new TopDownCamera();
  camera->initialize(Handle<TopDownCamera>(&camera));
  GameManager::getScreenManager()->getViewport()->setCamera(camera);

  Game::transitionToSplashScreen();

  GameManager::run();

  return 0;
}