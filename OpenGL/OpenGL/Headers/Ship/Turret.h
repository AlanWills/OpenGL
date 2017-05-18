#pragma once

#include "Objects/GameObject.h"


namespace SpaceGame
{

class DllExport Turret
{
  public:
    static void create(const Handle<GameObject>& turret);
};

}