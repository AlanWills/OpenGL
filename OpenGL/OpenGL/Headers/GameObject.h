#pragma once

#include "SpriteRenderer.h"
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

  virtual void draw(const SpriteRenderer& spriteRenderer) const;

  // State utility functions
  void setSolid(GLboolean isSolid) { m_solid = isSolid; }
  GLboolean isSolid() const { return m_solid; }

  void setDestroyed(GLboolean isDestroyed) { m_destroyed = isDestroyed; }
  GLboolean isDestroyed() const { return m_destroyed; }

  const glm::vec2& getPosition() const { return m_position; }
  void setPosition(const glm::vec2& position) { m_position = position; }
  void translate(const glm::vec2& deltaPosition) { m_position += deltaPosition; }

  const glm::vec2 getSize() const { return m_size; }

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

