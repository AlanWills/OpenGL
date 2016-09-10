#pragma once

#include "GLHeaders.h"
#include "SpriteRenderer.h"

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

  // Game state
  GameState              State;
  GLboolean              Keys[1024];
  GLuint                 Width, Height;
  // Constructor/Destructor
  Game(GLuint width, GLuint height);
  ~Game();

  // Initialize game state (load all shaders/textures/levels)
  void init();

  // GameLoop
  void handleInput(GLfloat elapsedGameTime);
  void update(GLfloat elapsedGameTime);
  void render(GLfloat percentageIntoFrame);

private:
  std::unique_ptr<SpriteRenderer> m_spriteRenderer;
};
