#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"


// Game-related State data
SpriteRenderer  *Renderer;


Game::Game(GLuint width, GLuint height)
  : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
  delete Renderer;
}

void Game::Init()
{
  // Load shaders
  ResourceManager::LoadShader("C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Shaders/Vertex/sprite.vs", "C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Shaders/Fragment/sprite.frag", nullptr, "sprite");
  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
  // Load textures
  ResourceManager::LoadTexture("C:/Users/Alan/Documents/Visual Studio 2015/Projects/OpenGL/OpenGL/OpenGL/Assets/awesomeface.png", GL_TRUE, "face");
  // Set render-specific controls
  Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
  Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}