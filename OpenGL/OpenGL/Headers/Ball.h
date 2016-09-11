#pragma once

#include "GameObject.h"

class Ball : public GameObject
{

public:
  Ball(GLfloat radius, const glm::vec2& position, Texture2D* texture, const glm::vec2& velocity);
  ~Ball();

  void update(GLfloat elapsedGameTime, GLuint windowWidth);
  void reset(const glm::vec2& position, const glm::vec2& velocity);

  GLboolean isStuck() const { return m_stuck; }
  void release() { m_stuck = GL_FALSE; }

private:
  GLfloat m_radius;
  GLboolean m_stuck;
};