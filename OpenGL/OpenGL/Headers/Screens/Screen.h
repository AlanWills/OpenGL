#pragma once

#include "Objects/GameObject.h"
#include "Memory/PoolAllocator.h"


namespace OpenGL
{
#define SCREEN_GAMEOBJECT_POOL_SIZE 10

class Screen : public Component
{
  public:
    Screen();
    virtual ~Screen();

    void initialize() override;

  private:
    PoolAllocator<GameObject, SCREEN_GAMEOBJECT_POOL_SIZE> m_gameObjects;
};

}