#pragma once

#include "Game/Game.h"
#include "Viewport/TopDownCamera.h"


namespace SpaceGame
{

class SpaceGame : public Game
{
  public:
    SpaceGame() : m_topDownCamera(nullptr) { }

  protected:
    void onInitialize() override;

  private:
    typedef Game Inherited;

    TopDownCamera* m_topDownCamera;
};

}