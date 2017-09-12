#pragma once

#include "Objects/Script.h"


using namespace CelesteEngine;

namespace CelesteEngine
{
  namespace Rendering
  {
    class SpriteRenderer;
  }

  namespace Input
  {
    class KeyboardRigidBody2DController;
  }
}

namespace SpaceGame
{

class PlayerController : public Script
{
  DECLARE_SCRIPT(PlayerController)

  public:
    float getMinPosition() const { return m_minPosition; }
    float getMaxPosition() const { return m_maxPosition; }
    float getNextLevelPosition() const { return m_nextLevelPosition; }

    void setMinPosition(float minPosition) { m_minPosition = minPosition; }
    void setMaxPosition(float maxPosition) { m_maxPosition = maxPosition; }
    void setNextLevelPosition(float nextLevelPosition) { m_nextLevelPosition = nextLevelPosition; }

  protected:
    void onSetGameObject(const Handle<GameObject>& gameObject) override;
    void onUpdate(GLfloat elapsedGameTime) override;

  private:
    typedef Script Inherited;

    Handle<Rendering::SpriteRenderer> m_playerRenderer;
    Handle<Input::KeyboardRigidBody2DController> m_controller;
    
    float m_minPosition;
    float m_maxPosition;
    float m_nextLevelPosition;
};

}