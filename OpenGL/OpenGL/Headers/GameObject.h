#pragma once

#include "SpriteRenderer.h"
#include "GLHeaders.h"
#include "glm/glm.hpp"

class GameObject
{

public:
  GameObject();
  GameObject(
    const glm::vec2& pos, 
    const glm::vec2& size, 
    Texture2D* texture,
    const glm::vec3& colour = glm::vec3(1.0f),
    const glm::vec2& velocity = glm::vec2(0.0f));

  ~GameObject();

  virtual void draw(const SpriteRenderer& spriteRenderer, GLfloat timeFromLastUpdate) const;

  // State utility functions
  void setSolid(GLboolean isSolid) { m_solid = isSolid; }
  GLboolean isSolid() const { return m_solid; }

  void destroy() { m_destroyed = GL_TRUE; }
  GLboolean isDestroyed() const { return m_destroyed; }

  const glm::vec2& getPosition() const { return m_position; }
  void setPosition(const glm::vec2& position) { m_position = position; }
  void setPositionX(GLfloat xPosition) { m_position.x = xPosition; }
  void setPositionY(GLfloat yPosition) { m_position.y = yPosition; }
  void translate(const glm::vec2& deltaPosition) { m_position += deltaPosition; }

  const glm::vec2& getSize() const { return m_size; }

  const glm::vec2& getVelocity() const { return m_velocity; }
  void setVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
  void reverseVelocityX() { m_velocity.x *= -1; }
  void reverseVelocityY() { m_velocity.y *= -1; }

private:
  glm::vec2 m_position;
  glm::vec2 m_size;
  glm::vec2 m_velocity;

  glm::vec3 m_colour;

  GLfloat m_rotation;

  GLboolean m_solid;
  GLboolean m_destroyed;

  Texture2D* m_texture;
};

