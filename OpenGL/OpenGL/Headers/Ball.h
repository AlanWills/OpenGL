#pragma once

#include "GameObject.h"


class Ball : public GameObject
{

public:
  Ball(const glm::vec2& playerPosition, Texture2D* texture);
  ~Ball();

  void update(GLfloat elapsedGameTime, GLuint windowWidth);
  void reset(const glm::vec2& position);

  GLboolean isStuck() const { return m_stuck; }
  void release();

  GLfloat getRadius() const { return getSize().x; }

  // Init data
  GLfloat getInitialBallRadius() { return 12.5f; }
  const glm::vec2& getInitialBallVelocity() 
  { 
    static glm::vec2 initialVelocity(100, -1000);

    return initialVelocity;
  }

private:
  GLboolean m_stuck;
};