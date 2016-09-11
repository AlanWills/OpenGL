#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Debug.h"


//------------------------------------------------------------------------------------------------
Game::Game(GLuint width, GLuint height)
: m_state(GAME_ACTIVE), 
  m_keys(), 
  m_width(width), 
  m_height(height),
  m_spriteRenderer(nullptr)
{

}

//------------------------------------------------------------------------------------------------
Game::~Game()
{

}

//------------------------------------------------------------------------------------------------
void Game::init()
{
  glCheckError();

  // Load shaders
  Shader* shader = ResourceManager::loadShader("sprite.vs", "sprite.frag", nullptr, "sprite");

  // Configure shaders
  shader->use(); 
  shader->setInteger("image", 0);
  shader->setMatrix4("projection", glm::ortho(0.0f, (GLfloat)m_width, (GLfloat)m_height, 0.0f, -1.0f, 1.0f));

  // Load textures
  ResourceManager::loadTexture("awesomeface.png", GL_TRUE, "face");
  
  m_spriteRenderer.reset(new SpriteRenderer(shader));

  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Game::update(GLfloat elapsedGameTime)
{

}

//------------------------------------------------------------------------------------------------
void Game::handleInput(GLfloat elapsedGameTime)
{

}

//------------------------------------------------------------------------------------------------
void Game::render(GLfloat percentageIntoFrame)
{
  m_spriteRenderer->drawSprite(ResourceManager::getTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}