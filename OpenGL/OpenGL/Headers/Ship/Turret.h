#pragma once

#include "Objects/GameObject.h"


namespace SpaceGame
{

class CelesteEngineDllExport Turret
{
  public:
    static void create(const Handle<GameObject>& turret);
};

}