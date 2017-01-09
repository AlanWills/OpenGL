#pragma once

#include "Scripts/Script.h"
#include "Maths/Transform.h"


namespace OpenGL
{

class KeyboardMovementScript : public Script
{
  DECLARE_COMPONENT(PoolAllocator, KeyboardMovementScript, 10)

  public:
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;

    void setMoveLeftKey(int moveLeftKey) { m_moveLeftKey = moveLeftKey; }
    void setMoveRightKey(int moveRightKey) { m_moveRightKey = moveRightKey; }
    void setMoveUpKey(int moveUpKey) { m_moveUpKey = moveUpKey; }
    void setMoveDownKey(int moveDownKey) { m_moveDownKey = moveDownKey; }

    void setPanSpeed(float panSpeed) { m_panSpeed = panSpeed; }

  private:
    typedef Script Inherited;

    Handle<Transform> m_transform;

    int m_moveLeftKey;
    int m_moveRightKey;
    int m_moveUpKey;
    int m_moveDownKey;

    float m_panSpeed;

    glm::vec3 m_directionVector;
};

}