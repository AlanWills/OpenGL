#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

class GameLevel
{
public:
  GameLevel();
  ~GameLevel();

  // Loads level from file
  void load(const std::string& file, GLuint levelWidth, GLuint levelHeight);

  // Render the level
  void draw(const SpriteRenderer& renderer) const;

  // Check if the level is completed (all non-solid tiles are destroyed)
  GLboolean isCompleted() const;

private:
  // Initialize the level using the tile info
  void init(const std::vector<std::vector<GLuint>>& tileData, GLuint levelWidth, GLuint levelHeight);

  std::vector<std::unique_ptr<GameObject>> m_bricks;
};
