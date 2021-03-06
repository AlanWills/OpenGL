#include "stdafx.h"

#include "Scripts/AsteroidSpawningScript.h"
#include "Physics/RigidBody2D.h"
#include "Screens/Screen.h"
#include "Rendering/SpriteRenderer.h"

using namespace CelesteEngine::Rendering;


namespace SpaceGame
{
  // Initialize static variables
  Path AsteroidSpawningScript::m_tinyAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidTiny.png");
  Path AsteroidSpawningScript::m_smallAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidSmall.png");
  Path AsteroidSpawningScript::m_largeAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidLarge.png");
  Path AsteroidSpawningScript::m_hugeAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidHuge.png");

  REGISTER_SCRIPT(AsteroidSpawningScript, ASTEROID_SPAWNING_SCRIPT_POOLSIZE);

  //------------------------------------------------------------------------------------------------
  AsteroidSpawningScript::AsteroidSpawningScript() :
    m_bounds(),
    m_tinyAsteroidCount(0),
    m_smallAsteroidCount(0),
    m_largeAsteroidCount(0),
    m_hugeAsteroidCount(0),
    m_random(time(nullptr))
  {
  }

  //------------------------------------------------------------------------------------------------
  AsteroidSpawningScript::~AsteroidSpawningScript()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AsteroidSpawningScript::onAwake()
  {
    Inherited::onAwake();

    ASSERT(!getGameObject().is_null());
    m_bounds = getGameObject()->findComponent<RectangleCollider>();
    ASSERT(!m_bounds.is_null());

    createAsteroids();
  }

  //------------------------------------------------------------------------------------------------
  void AsteroidSpawningScript::onUpdate(GLfloat secondsPerUpdate)
  {
    Inherited::onUpdate(secondsPerUpdate);

    // These asteroids will be contiguous in memory so this is still efficient iterating
    for (const Handle<CelesteEngine::GameObject>& asteroid : m_asteroids)
    {
      const Handle<RectangleCollider>& collider = asteroid->findComponent<RectangleCollider>();
      ASSERT(!collider.is_null());

      if (collider->left().x > m_bounds->right().x)
      {
        asteroid->getTransform()->translate(-m_bounds->width() - collider->width(), 0, 0);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void AsteroidSpawningScript::createAsteroids()
  {
    for (int i = 0; i < m_tinyAsteroidCount; ++i)
    {
      createAsteroid(m_tinyAsteroidTexturePath);
    }

    for (int i = 0; i < m_smallAsteroidCount; ++i)
    {
      createAsteroid(m_smallAsteroidTexturePath);
    }

    for (int i = 0; i < m_largeAsteroidCount; ++i)
    {
      createAsteroid(m_largeAsteroidTexturePath);
    }

    for (int i = 0; i < m_hugeAsteroidCount; ++i)
    {
      createAsteroid(m_hugeAsteroidTexturePath);
    }
  }

  //------------------------------------------------------------------------------------------------
  void AsteroidSpawningScript::createAsteroid(const Path& asteroidTexturePath)
  {
    /*const Handle<CelesteEngine::GameObject>& asteroid = GameObject::allocate(Handle<Screen>());
    asteroid->getTransform()->setParent(getTransform());
    asteroid->getTransform()->setTranslation(glm::vec3(generateAsteroidPosition(), 0));

    SpriteRenderer::create(asteroid, asteroidTexturePath);
    RigidBody2D::create(asteroid, generateAsteroidLinearVelocity(), generateAsteroidAngularVelocity());

    const Handle<SpriteRenderer>& renderer = asteroid->findComponent<SpriteRenderer>();

    RectangleCollider::create(asteroid, renderer->getDimensions());

    m_asteroids.push_back(asteroid);*/
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 AsteroidSpawningScript::generateAsteroidPosition() const
  {
    const glm::vec2& halfScreenDims = glm::vec2() * 0.5f;
    return glm::vec2(m_random.generate(-halfScreenDims.x, halfScreenDims.x), m_random.generate(-halfScreenDims.y, halfScreenDims.y));
  }

  //------------------------------------------------------------------------------------------------
  void createAsteroidSpawner(
    const Handle<CelesteEngine::GameObject>& asteroidSpawner,
    float tinyAsteroidCount,
    float smallAsteroidCount,
    float largeAsteroidCount,
    float hugeAsteroidCount)
  {
    /*const glm::vec2& screenDimensions = getViewportDimensions();*/
    glm::vec2 screenDimensions;
    asteroidSpawner->getTransform()->translate(screenDimensions * 0.5f);

    RectangleCollider::create(asteroidSpawner, screenDimensions);

    const Handle<AsteroidSpawningScript>& asteroidSpawning = asteroidSpawner->addComponent<AsteroidSpawningScript>();
    asteroidSpawning->setTinyAsteroidCount(tinyAsteroidCount);
    asteroidSpawning->setSmallAsteroidCount(smallAsteroidCount);
    asteroidSpawning->setLargeAsteroidCount(largeAsteroidCount);
    asteroidSpawning->setHugeAsteroidCount(hugeAsteroidCount);
  }
}