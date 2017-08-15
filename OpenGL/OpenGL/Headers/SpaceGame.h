#pragma once

#include "Game/Game.h"


namespace SpaceGame
{

class SpaceGame : public Game
{
  public:
    SpaceGame() { }

  protected:
    void onInitialize() override;

  private:
    typedef Game Inherited;
};

}