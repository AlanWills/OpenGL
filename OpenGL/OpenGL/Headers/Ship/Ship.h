#pragma once

#include "DllExport.h"
#include "Objects/GameObject.h"


namespace SpaceGame
{

class DllExport Ship
{
  public:
    static void create(const Handle<CelesteEngine::GameObject>& gameObject);
};

}