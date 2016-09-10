#include "Game.h"
#include "ResourceManager.h"


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
  // Load shaders
  Shader* shader = ResourceManager::loadShader("sprite", "sprite.vs", "sprite.frag");

  glm::mat4 projection = glm::ortho(0.0f, (GLfloat)m_width, (GLfloat)m_height, 0.0f, -1.0f, 1.0f);
  shader->use();
  shader->setInt(0, TEXTURE);
  shader->setMatrix(projection, PROJECTION_MATRIX);

  m_spriteRenderer.reset(new SpriteRenderer(shader));

  ResourceManager::loadTexture("awesomeface.png", GL_TRUE, "face");
}

//------------------------------------------------------------------------------------------------
void Game::handleInput(GLfloat elapsedTime)
{

}

//------------------------------------------------------------------------------------------------
void Game::update(GLfloat elapsedTime)
{

}

//------------------------------------------------------------------------------------------------
void Game::draw(GLfloat percentageIntoFrame)
{
  m_spriteRenderer->drawSprite(
    *ResourceManager::getTexture("face"), 
    glm::vec2(200, 200), 
    glm::vec2(300, 400), 45.0f, 
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}