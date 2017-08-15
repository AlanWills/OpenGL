#include "stdafx.h"

#include "SpaceGame.h"
#include "Factories/GameScreenFactory.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void SpaceGame::onInitialize()
  {
    Inherited::onInitialize();

    GameScreenFactory::transitionToSplashScreen();
  }
}