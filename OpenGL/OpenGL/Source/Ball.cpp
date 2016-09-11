#include "Ball.h"


//------------------------------------------------------------------------------------------------
Ball::Ball(GLfloat radius, const glm::vec2& position, Texture2D* texture, const glm::vec2& velocity)
: m_radius(radius),
  GameObject(position, glm::vec2(radius), texture),
  m_stuck(GL_TRUE)
{
  setVelocity(velocity);
}

//------------------------------------------------------------------------------------------------
Ball::~Ball()
{
}

//------------------------------------------------------------------------------------------------
void Ball::update(GLfloat elapsedGameTime, GLuint windowWidth)
{
  if (!m_stuck)
  {
    const glm::vec2& position = getPosition();
    translate(getVelocity() * elapsedGameTime);

    if (position.x <= 0)
    {
      reverseVelocityX();
      setPositionX(0);
    }
    else if (position.x + getSize().x >= windowWidth)
    {
      reverseVelocityX();
      setPositionX(windowWidth - getSize().x);
    }

    if (position.y <= 0)
    {
      reverseVelocityY();
      setPositionY(0);
    }
  }
}

//------------------------------------------------------------------------------------------------
void Ball::reset(const glm::vec2& position, const glm::vec2& velocity)
{
  setPosition(position);
  setVelocity(velocity);
  m_stuck = true;
}