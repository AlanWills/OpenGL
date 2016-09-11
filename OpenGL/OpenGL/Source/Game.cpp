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
  m_currentLevel(0),
  m_player(nullptr)
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
  ResourceManager::loadTexture("paddle.png", GL_TRUE, "paddle");

  // Load levels
  loadLevel("One.txt");
  loadLevel("Two.txt");
  loadLevel("Three.txt");
  loadLevel("Four.txt");
  
  m_spriteRenderer.reset(new SpriteRenderer(shader));

  glm::vec2 playerPos((m_width - m_playerSize.x) * 0.5f, m_height - m_playerSize.y);
  m_player.reset(new GameObject(playerPos, m_playerSize, ResourceManager::getTexture("paddle")));

  glm::vec2 ballPos(playerPos.x + m_playerSize.x * 0.5f - m_ballRadius, playerPos.y - m_ballRadius * 0.5f);
  m_ball.reset(new Ball(m_ballRadius, ballPos, ResourceManager::getTexture("face"), m_initialBallVelocity));

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
void Game::handleInput(GLfloat elapsedGameTime)
{
  if (m_state == GAME_ACTIVE)
  {
    GLfloat velocity = 0;

    // Move paddle
    if (m_keys[GLFW_KEY_A])
    {
      if (m_player->getPosition().x >= 0)
      {
        velocity = -m_playerVelocity * elapsedGameTime;
      }
    }

    if (m_keys[GLFW_KEY_D])
    {
      if (m_player->getPosition().x <= m_width - m_player->getSize().x)
      {
        velocity = m_playerVelocity * elapsedGameTime;
      }
    }

    if (m_keys[GLFW_KEY_SPACE])
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
}

//------------------------------------------------------------------------------------------------
void Game::render(GLfloat percentageIntoFrame)
{
  if (m_state == GAME_ACTIVE)
  {
    // Draw background
    m_spriteRenderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0), glm::vec2(m_width, m_height));
    m_levels[m_currentLevel]->draw(*m_spriteRenderer);
    m_player->draw(*m_spriteRenderer);
    m_ball->draw(*m_spriteRenderer);
  }
}