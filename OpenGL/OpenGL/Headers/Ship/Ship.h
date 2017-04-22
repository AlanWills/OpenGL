#pragma once

#include "DllExport.h"
#include "Objects/GameObject.h"


namespace SpaceGame
{

class DllExport Ship
{
  public:
    static void createShip(const Handle<CelesteEngine::GameObject>& gameObject);
};

}