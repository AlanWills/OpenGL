#include "stdafx.h"

#include "SpaceGame.h"
#include "Factories/GameScreenFactory.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void SpaceGame::onInitialize()
  {
    Inherited::onInitialize();

    // Add to onInitialize override
    m_topDownCamera = new TopDownCamera();
    m_topDownCamera->initialize(Handle<TopDownCamera>(&m_topDownCamera));

    // Viewport takes ownership of camera now
    getViewport()->setCamera(m_topDownCamera);

    transitionToSplashScreen();
  }
}