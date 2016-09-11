#pragma once

#include "GLHeaders.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"

#include <memory>


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
  Game(GLuint width, GLuint height);
  ~Game();

  // Initialize game state (load all shaders/textures/levels)
  void init();

  // GameLoop
  void handleInput(GLfloat elapsedGameTime);
  void update(GLfloat elapsedGameTime);
  void render(GLfloat percentageIntoFrame);

  void setKeyState(int key, bool keyState) { m_keys[key] = keyState; }

private:
  std::unique_ptr<SpriteRenderer> m_spriteRenderer;
  std::vector<std::unique_ptr<GameLevel>> m_levels;

  // Game state
  GameState  m_state;
  GLboolean  m_keys[1024];
  GLuint     m_width;
  GLuint     m_height;
};
