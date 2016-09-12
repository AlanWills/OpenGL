#include "Ball.h"


//------------------------------------------------------------------------------------------------
Ball::Ball(const glm::vec2& playerPosition, Texture2D* texture)
: GameObject(playerPosition - glm::vec2(getInitialBallRadius() * 0.5f), glm::vec2(getInitialBallRadius()), texture),
  m_stuck(GL_TRUE)
{
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
void Ball::release()
{
  m_stuck = GL_FALSE;
  setVelocity(getInitialBallVelocity());
}

//------------------------------------------------------------------------------------------------
void Ball::reset(const glm::vec2& position)
{
  setPosition(position - glm::vec2(getInitialBallRadius() * 0.5f));
  setVelocity(glm::vec2(0));

  m_stuck = true;
}