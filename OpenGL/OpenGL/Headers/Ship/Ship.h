#pragma once

#include "CelesteEngineDllExport.h"
#include "Objects/GameObject.h"


namespace SpaceGame
{

class CelesteEngineDllExport Ship
{
  public:
    static void create(const Handle<CelesteEngine::GameObject>& gameObject);
};

}