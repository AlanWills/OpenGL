#pragma once

#include "DllExport.h"
#include "Objects/Component.h"


namespace SpaceGame
{

class KeyboardShipController : public CelesteEngine::Component
{
  DECLARE_COMPONENT(CelesteEngine::PoolAllocator, KeyboardShipController, 10)

  public:
    void handleInput(GLfloat elapsedGameTime) override;

    int getMoveForwardKey() const { return m_moveForwardKey; }
    void setMoveForwardKey(int key) { m_moveForwardKey = key; }
    
    int getMoveBackwardKey() const { return m_moveBackwardKey; }
    void setMoveBackwardKey(int key) { m_moveBackwardKey = key; }

  private:
    typedef CelesteEngine::Component Inherited;

    int m_moveForwardKey;
    int m_moveBackwardKey;
};

}