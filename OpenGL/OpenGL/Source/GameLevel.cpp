#include "GameLevel.h"
#include "ResourceManager.h"

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
void GameLevel::draw(const SpriteRenderer& renderer) const
{
  for (const std::unique_ptr<GameObject>& brick : m_bricks)
  {
    brick->draw(renderer);
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