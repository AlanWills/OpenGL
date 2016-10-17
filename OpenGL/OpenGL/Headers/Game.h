#pragma once

#include "GLHeaders.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "Ball.h"

#include <memory>
#include <unordered_map>

const glm::vec2 m_playerSize(100.0f, 20.0f);
const GLfloat m_playerVelocity(500.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
  // Represents the current state of the game
  enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
  };

  // Constructor/Destructor
  Game();
  ~Game();

  // Initialize game state (load all shaders/textures/levels)
  void init();

  // GameLoop
  void handleInput(GLfloat elapsedGameTime);
  void update(GLfloat elapsedGameTime);
  void render(GLfloat timeFromLastUpdate);

  void setKeyState(int key, bool keyState) { m_keys[key] = keyState; }

private:
  void loadLevel(const std::string& levelPath);

  void resetLevel();
  void resetPlayer();

  std::unique_ptr<SpriteRenderer> m_spriteRenderer;
  std::vector<std::unique_ptr<GameLevel>> m_levels;

  const std::unordered_map<GLuint, std::string> m_levelFiles = {
    { 0, "One.txt" },
    { 1, "Two.txt" },
    { 2, "Three.txt" },
    { 3, "Four.txt" }
  };

  GLuint m_currentLevel;

  // Game state
  GameState  m_state;
  GLboolean  m_keys[1024];
  GLuint     m_width;
  GLuint     m_height;

  std::unique_ptr<GameObject> m_player;
  std::unique_ptr<Ball> m_ball;
};
