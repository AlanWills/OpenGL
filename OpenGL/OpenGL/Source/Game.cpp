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
  m_spriteRenderer(nullptr),
  m_currentLevel(0)
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
  ResourceManager::loadTexture("background.jpg", GL_FALSE, "background");
  ResourceManager::loadTexture("awesomeface.png", GL_TRUE, "face");
  ResourceManager::loadTexture("block.png", GL_FALSE, "block");
  ResourceManager::loadTexture("block_solid.png", GL_FALSE, "block_solid");

  // Load levels
  loadLevel("One.txt");
  loadLevel("Two.txt");
  loadLevel("Three.txt");
  loadLevel("Four.txt");
  
  m_spriteRenderer.reset(new SpriteRenderer(shader));

  glCheckError();
}

//------------------------------------------------------------------------------------------------
void Game::loadLevel(const std::string& levelPath)
{
  std::string fullPath(DIRECTORY);
  fullPath.append(LEVEL_DIR);
  fullPath += levelPath;

  GameLevel* level = new GameLevel();
  level->load(fullPath, m_width, m_height * 0.5f);
  m_levels.push_back(std::unique_ptr<GameLevel>(level));
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
  if (m_state == GAME_ACTIVE)
  {
    // Draw background
    m_spriteRenderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0), glm::vec2(m_width, m_height));
    m_levels[m_currentLevel]->draw(*m_spriteRenderer);
  }
}