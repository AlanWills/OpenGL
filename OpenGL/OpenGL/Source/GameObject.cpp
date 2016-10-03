#include "GameObject.h"

//------------------------------------------------------------------------------------------------
GameObject::GameObject()
: m_position(0, 0),
  m_size(1, 1),
  m_velocity(0.0f),
  m_colour(1.0f),
  m_rotation(0.0f),
  m_texture(nullptr),
  m_solid(false),
  m_destroyed(false)
{
}

//------------------------------------------------------------------------------------------------
GameObject::GameObject(
  const glm::vec2& pos,
  const glm::vec2& size,
  Texture2D* texture,
  const glm::vec3& colour,
  const glm::vec2& velocity)
: m_position(pos),
  m_size(size),
  m_texture(texture),
  m_colour(colour),
  m_velocity(velocity),
  m_solid(false),
  m_destroyed(false)
{
}

//------------------------------------------------------------------------------------------------
GameObject::~GameObject()
{
}

//------------------------------------------------------------------------------------------------
void GameObject::draw(const SpriteRenderer& spriteRenderer, GLfloat timeFromLastUpdate) const
{
  glm::vec2 interpolatedPos(m_position);
  interpolatedPos += m_velocity * timeFromLastUpdate;
  spriteRenderer.drawSprite(m_texture, interpolatedPos, m_size, m_rotation, m_colour);
}