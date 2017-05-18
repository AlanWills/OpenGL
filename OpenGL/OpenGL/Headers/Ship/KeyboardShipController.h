#pragma once

#include "DllExport.h"
#include "Objects/Script.h"


namespace SpaceGame
{

class KeyboardShipController : public CelesteEngine::Script
{
  DECLARE_SCRIPT(KeyboardShipController, 10)

  public:
    void handleInput(GLfloat elapsedGameTime) override;

    float getLinearSpeed() const { return m_linearSpeed; }
    void setLinearSpeed(float linearSpeed) { m_linearSpeed = linearSpeed; }

    float getAngularSpeed() const { return m_angularSpeed; }
    void setAngularSpeed(float angularSpeed) { m_angularSpeed = angularSpeed; }

    int getMoveForwardKey() const { return m_moveForwardKey; }
    void setMoveForwardKey(int key) { m_moveForwardKey = key; }
    
    int getMoveBackwardKey() const { return m_moveBackwardKey; }
    void setMoveBackwardKey(int key) { m_moveBackwardKey = key; }

    int getRotateLeftKey() const { return m_rotateLeftKey; }
    void setRotateLeftKey(int key) { m_rotateLeftKey = key; }

    int getRotateRightKey() const { return m_rotateRightKey; }
    void setRotateRightKey(int key) { m_rotateRightKey = key; }

  private:
    typedef CelesteEngine::Script Inherited;

    float m_linearSpeed;
    float m_angularSpeed;

    int m_moveForwardKey;
    int m_moveBackwardKey;
    int m_rotateLeftKey;
    int m_rotateRightKey;
};

}