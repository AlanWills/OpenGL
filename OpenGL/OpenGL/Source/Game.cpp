#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Input/InputManager.h"

using namespace Engine;

//------------------------------------------------------------------------------------------------
Game::Game()
: m_state(GAME_ACTIVE), 
  m_keys(), 
  m_spriteRenderer(nullptr),
  m_currentLevel(0),
  m_player(nullptr)
{
}

//------------------------------------------------------------------------------------------------
Game::~Game()
{
}

//------------------------------------------------------------------------------------------------
void Game::init(GLFWwindow* window)
{
  InputManager::init(window);

  m_width = 800;
  m_height = 600;

  //glCheckError();

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
  ResourceManager::loadTexture("paddle.png", GL_TRUE, "paddle");

  // Load levels
  for (const std::pair<int, std::string>& levelPairs : m_levelFiles)
  {
    loadLevel(levelPairs.second);
  }
  
  m_spriteRenderer.reset(new SpriteRenderer(shader));

  glm::vec2 playerPos((m_width - m_playerSize.x) * 0.5f, m_height - m_playerSize.y);
  m_player.reset(new GameObject(playerPos, m_playerSize, ResourceManager::getTexture("paddle")));

  glm::vec2 ballPos(playerPos.x + m_playerSize.x * 0.5f, playerPos.y);
  m_ball.reset(new Ball(ballPos, ResourceManager::getTexture("face")));

  //glCheckError();
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
void Game::handleInput(GLfloat elapsedGameTime)
{
  InputManager::update(elapsedGameTime);
  Keyboard* keyboard = InputManager::getKeyboard();

  if (m_state == GAME_ACTIVE)
  {
    GLfloat velocity = 0;

    // Move paddle
    if (keyboard->isKeyDown(GLFW_KEY_A))
    {
      if (m_player->getPosition().x >= 0)
      {
        velocity = -m_playerVelocity * elapsedGameTime;
      }
    }

    if (keyboard->isKeyDown(GLFW_KEY_D))
    {
      if (m_player->getPosition().x <= m_width - m_player->getSize().x)
      {
        velocity = m_playerVelocity * elapsedGameTime;
      }
    }

    if (keyboard->isKeyDown(GLFW_KEY_SPACE))
    {
      m_ball->release();
    }

    glm::vec2 delta(velocity, 0);
    m_player->translate(delta);

    if (m_ball->isStuck())
    {
      m_ball->translate(delta);
    }
  }
}

//------------------------------------------------------------------------------------------------
void Game::update(GLfloat elapsedGameTime)
{
  m_ball->update(elapsedGameTime, m_width);
  m_levels[m_currentLevel]->doCollisions(m_ball.get(), m_player.get());

  if (m_ball->getPosition().y >= m_height)
  {
    resetLevel();
    resetPlayer();
  }
}

//------------------------------------------------------------------------------------------------
void Game::resetLevel()
{
  std::string fullLevelPath(DIRECTORY);
  fullLevelPath.append(LEVEL_DIR);
  fullLevelPath.append(m_levelFiles.at(m_currentLevel));

  m_levels[m_currentLevel]->load(fullLevelPath, m_width, m_height * 0.5f);
}

//------------------------------------------------------------------------------------------------
void Game::resetPlayer()
{
  glm::vec2 playerPos((m_width - m_playerSize.x) * 0.5f, m_height - m_playerSize.y);
  m_player->setPosition(playerPos);

  glm::vec2 ballPos(playerPos.x + m_playerSize.x * 0.5f, playerPos.y);
  m_ball->reset(ballPos);
}

//------------------------------------------------------------------------------------------------
void Game::render(GLfloat elapsedGameTime, GLfloat percentageIntoFrame)
{
  if (m_state == GAME_ACTIVE)
  {
    // Draw background
    m_spriteRenderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0), glm::vec2(m_width, m_height));
    m_levels[m_currentLevel]->draw(*m_spriteRenderer, elapsedGameTime, percentageIntoFrame);
    m_player->draw(*m_spriteRenderer, elapsedGameTime, percentageIntoFrame);
    m_ball->draw(*m_spriteRenderer, elapsedGameTime, percentageIntoFrame);
  }
}