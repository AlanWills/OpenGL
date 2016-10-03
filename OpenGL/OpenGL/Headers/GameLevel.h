#pragma once

#include <vector>
#include <memory>

#include "GameObject.h"

class Ball;

enum Direction
{
  kUp,
  kRight,
  kDown,
  kLeft
};

class GameLevel
{
public:
  GameLevel();
  ~GameLevel();

  typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

  // Loads level from file
  void load(const std::string& file, GLuint levelWidth, GLuint levelHeight);

  void doCollisions(Ball* ball, GameObject* player);

  // Render the level
  void draw(const SpriteRenderer& renderer, GLfloat timeFromLastUpdate) const;

  // Check if the level is completed (all non-solid tiles are destroyed)
  GLboolean isCompleted() const;

private:
  // Initialize the level using the tile info
  void init(const std::vector<std::vector<GLuint>>& tileData, GLuint levelWidth, GLuint levelHeight);

  Collision checkCollision(const Ball* ball, const GameObject* gameObject);
  Direction vectorDirection(const glm::vec2& target);

  std::vector<std::unique_ptr<GameObject>> m_bricks;
};
