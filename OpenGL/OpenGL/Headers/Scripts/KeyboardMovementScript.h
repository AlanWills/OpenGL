#pragma once

#include "Script.h"
#include "Maths/Transform.h"


namespace OpenGL
{

class KeyboardMovementScript : public Script
{
  DECLARE_COMPONENT(KeyboardMovementScript, 10)

  public:
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;

    void setTransform(Transform* transform) { m_transform = transform; }

    void setMoveLeftKey(int moveLeftKey) { m_moveLeftKey = moveLeftKey; }
    void setMoveRightKey(int moveRightKey) { m_moveRightKey = moveRightKey; }
    void setMoveUpKey(int moveUpKey) { m_moveUpKey = moveUpKey; }
    void setMoveDownKey(int moveDownKey) { m_moveDownKey = moveDownKey; }

    void setPanSpeed(float panSpeed) { m_panSpeed = panSpeed; }

  private:
    typedef Component Inherited;

    Transform* m_transform;

    int m_moveLeftKey;
    int m_moveRightKey;
    int m_moveUpKey;
    int m_moveDownKey;

    float m_panSpeed;

    glm::vec3 m_directionVector;
};

}