#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Debug.h"


//------------------------------------------------------------------------------------------------
Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), 
  Keys(), 
  Width(width), 
  Height(height),
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
  ResourceManager::LoadShader("C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Shaders/Vertex/sprite.vs", "C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Shaders/Fragment/sprite.frag", nullptr, "sprite");

  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
  Shader& shader = ResourceManager::GetShader("sprite");
  shader.use();
  shader.setInteger("image", 0);
  shader.setMatrix4("projection", projection);

  // Load textures
  ResourceManager::LoadTexture("C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Assets/awesomeface.png", GL_TRUE, "face");
  
  m_spriteRenderer.reset(new SpriteRenderer(ResourceManager::GetShader("sprite")));

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
  m_spriteRenderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}