#include "GameLevel.h"
#include "ResourceManager.h"
#include "Ball.h"

#include <fstream>
#include <sstream>


//------------------------------------------------------------------------------------------------
GameLevel::GameLevel()
{
}

//------------------------------------------------------------------------------------------------
GameLevel::~GameLevel()
{
}

//------------------------------------------------------------------------------------------------
void GameLevel::load(const std::string& file, GLuint levelWidth, GLuint levelHeight)
{
  // Clear old data
  m_bricks.clear();

  // Load from file
  GLuint tileCode;
  std::string line;
  std::ifstream fStream(file);
  assert(fStream.good());

  std::vector<std::vector<GLuint>> tileData;

  // Read each line from level file
  while (std::getline(fStream, line))
  {
    std::istringstream sStream(line);
    std::vector<GLuint> row;

    // Read each word separated by spaces
    while (sStream >> tileCode)
    {
      row.push_back(tileCode);
    }

    tileData.push_back(row);
  }

  init(tileData, levelWidth, levelHeight);
}

//------------------------------------------------------------------------------------------------
void GameLevel::init(
  const std::vector<std::vector<GLuint>>& tileData, 
  GLuint levelWidth, 
  GLuint levelHeight)
{
  // Calculate dimensions
  GLfloat height = (GLfloat)tileData.size();
  GLfloat width = (GLfloat)tileData[0].size();
  GLfloat unitWidth = levelWidth / width;
  GLfloat unitHeight = levelHeight / height;

  // Initialize level tiles based on tileData

  for (GLuint y = 0; y < height; ++y)
  {
    for (GLuint x = 0; x < width; ++x)
    {
      if (tileData[y][x] == 0)
      {
        // NO-OP for empty tiles
        continue;
      }

      glm::vec2 pos(unitWidth * x, unitHeight * y);
      glm::vec2 size(unitWidth, unitHeight);
      glm::vec3 colour = glm::vec3(1.0f);
      GLboolean isSolid = GL_FALSE;
      std::string textureAsset("block");

      if (tileData[y][x] == 1) // Solid
      {
        textureAsset = "block_solid";
        colour = glm::vec3(0.8f, 0.8f, 0.7f);
        isSolid = GL_TRUE;
      }
      else if (tileData[y][x] > 1)
      {
        switch (tileData[y][x])
        {
          case 2:
            colour = glm::vec3(0.2f, 0.6f, 1.0f);
            break;

          case 3:
            colour = glm::vec3(0.0f, 0.7f, 0.0f);
            break;

          case 4:
            colour = glm::vec3(0.8f, 0.8f, 0.4f);
            break;

          case 5:
            colour = glm::vec3(1.0f, 0.5f, 0.0f);
            break;
        }
      }

      GameObject* obj = new GameObject(pos,
        size,
        ResourceManager::getTexture(textureAsset),
        colour);
      obj->setSolid(isSolid);
      m_bricks.push_back(std::unique_ptr<GameObject>(obj));
    }
  }
}

//------------------------------------------------------------------------------------------------
void GameLevel::doCollisions(Ball* ball, GameObject* player)
{
  for (const std::unique_ptr<GameObject>& brick : m_bricks)
  {
    if (!brick->isDestroyed())
    {
      Collision collisionResult = checkCollision(ball, brick.get());
      if (std::get<0>(collisionResult))
      {
        if (!brick->isSolid())
        {
          brick->destroy();
        }

        // Collision resolution
        Direction dir = std::get<1>(collisionResult);
        glm::vec2 diff_vector = std::get<2>(collisionResult);

        glm::vec2 translation;

        if (dir == kLeft || dir == kRight) // Horizontal collision
        {
          ball->reverseVelocityX(); // Reverse horizontal velocity                                      
          GLfloat penetration = ball->getRadius() - std::abs(diff_vector.x);

          if (dir == kLeft)
          {
            translation.x = penetration; // Move ball to right
          }
          else
          {
            translation.x = -penetration; // Move ball to left;
          }
        }
        else // Vertical collision
        {
          ball->reverseVelocityY(); // Reverse vertical velocity
          GLfloat penetration = ball->getRadius() - std::abs(diff_vector.y);

          if (dir == kUp)
          {
            translation.y = penetration; // Move ball back up
          }
          else
          {
            translation.y = penetration; // Move ball back down
          }
        }

        ball->translate(translation);

        return;
      }
    }
  }

  Collision collisionResult = checkCollision(ball, player);
  if (!ball->isStuck() && std::get<0>(collisionResult))
  {
    // Check where it hit the board, and change velocity based on where it hit the board
    GLfloat centerBoard = player->getPosition().x + player->getSize().x * 0.5f;
    GLfloat distance = (ball->getPosition().x + ball->getRadius()) - centerBoard;

    GLfloat percentage = distance / (player->getSize().x * 0.5f);
    GLfloat strength = 2.0f;

    const glm::vec2& oldVelocity = ball->getVelocity();
    glm::vec2 newVel(oldVelocity);

    newVel.x = ball->getInitialBallVelocity().x * percentage * strength;
    newVel.y = -abs(oldVelocity.y);
    ball->setVelocity(glm::normalize(newVel) * glm::length(oldVelocity));
  }
}

//------------------------------------------------------------------------------------------------
GameLevel::Collision GameLevel::checkCollision(const Ball* ball, const GameObject* gameObject)
{
  const glm::vec2& ballPosition = ball->getPosition();
  const glm::vec2& brickPosition = gameObject->getPosition();

  GLfloat ballRadius = ball->getRadius();
  const glm::vec2& brickSize = gameObject->getSize();

  glm::vec2 delta = ballPosition - glm::max(brickPosition, glm::min(ballPosition, brickPosition + brickSize));

  if ((delta.x * delta.x + delta.y * delta.y) < (ballRadius * ballRadius))
  {
    return std::make_tuple(GL_TRUE, vectorDirection(delta), delta);
  }

  return std::make_tuple(GL_FALSE, kUp, glm::vec2(0));
}

//------------------------------------------------------------------------------------------------
Direction GameLevel::vectorDirection(const glm::vec2& target)
{
  glm::vec2 compass[] = {
    glm::vec2(0.0f, 1.0f),	// up
    glm::vec2(1.0f, 0.0f),	// right
    glm::vec2(0.0f, -1.0f),	// down
    glm::vec2(-1.0f, 0.0f)	// left
  };

  GLfloat max = 0.0f;
  GLuint best_match = -1;
  for (GLuint i = 0; i < 4; i++)
  {
    GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
    if (dot_product > max)
    {
      max = dot_product;
      best_match = i;
    }
  }

  return (Direction)best_match;
}

//------------------------------------------------------------------------------------------------
void GameLevel::draw(const SpriteRenderer& renderer, GLfloat elapsedGameTime, GLfloat percentageIntoFrame) const
{
  for (const std::unique_ptr<GameObject>& brick : m_bricks)
  {
    if (!brick->isDestroyed())
    {
      brick->draw(renderer, elapsedGameTime, percentageIntoFrame);
    }
  }
}

//------------------------------------------------------------------------------------------------
GLboolean GameLevel::isCompleted() const
{
  for (const std::unique_ptr<GameObject>& brick : m_bricks)
  {
    if (!brick->isSolid() && !brick->isDestroyed())
    {
      return GL_FALSE;
    }
  }

  return GL_TRUE;
}