#pragma once

#include "GLHeaders.h"
#include "SpriteRenderer.h"

#include <memory.h>

class Game
{

public:
  Game(GLuint width, GLuint height);
  ~Game();

  // Represents the current state of the game
  enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
  };

  // Game loop functions
  void init();
  void handleInput(GLfloat elapsedTime);
  void update(GLfloat elapsedTime);
  void draw(GLfloat percentageIntoFrame);

  void setKey(int key, bool keyStatus) { m_keys[key] = keyStatus; }

private:
  std::unique_ptr<SpriteRenderer> m_spriteRenderer;

  GameState m_state;
  bool m_keys[1024];

  GLfloat m_width;
  GLfloat m_height;
};

