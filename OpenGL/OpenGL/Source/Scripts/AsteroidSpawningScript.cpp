#include "stdafx.h"

#include "Scripts/AsteroidSpawningScript.h"
#include "Physics/RigidBody2D.h"
#include "Screens/Screen.h"


namespace Game
{
  // Initialize static variables
  Path AsteroidSpawningScript::m_tinyAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidTiny.png");
  Path AsteroidSpawningScript::m_smallAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidSmall.png");
  Path AsteroidSpawningScript::m_largeAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidLarge.png");
  Path AsteroidSpawningScript::m_hugeAsteroidTexturePath = Path("Sprites", "Asteroids", "AsteroidHuge.png");

  REGISTER_COMPONENT(AsteroidSpawningScript);

  //------------------------------------------------------------------------------------------------
  AsteroidSpawningScript::AsteroidSpawningScript() :
    m_bounds(nullptr),
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
  void AsteroidSpawningScript::awake()
  {
    Inherited::awake();

    ASSERT(getParent().get());
    m_bounds = getParent()->findComponent<RectangleCollider>();
    ASSERT(m_bounds.get());

    createAsteroids();
  }

  //------------------------------------------------------------------------------------------------
  void AsteroidSpawningScript::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    // These asteroids will be contiguous in memory so this is still efficient iterating
    for (const Handle<CelesteEngine::GameObject>& asteroid : m_asteroids)
    {
      const Handle<RectangleCollider>& collider = asteroid->findComponent<RectangleCollider>();
      ASSERT(collider.get());

      if (collider->left() > m_bounds->right())
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
    const Handle<Screen>& currentScreen = getCurrentScreen();
    
    if (!currentScreen->canAllocateGameObject())
    {
      ASSERT_FAIL("Out of game objects.  Consider increasing pool size");
      return;
    }

    const Handle<CelesteEngine::GameObject>& asteroid = currentScreen->allocateAndInitializeGameObject();
    asteroid->getTransform()->setParent(getParent()->getTransform());
    asteroid->getTransform()->setTranslation(glm::vec3(generateAsteroidPosition(), 0));

    createSprite(asteroid, asteroidTexturePath);
    createRigidBody2D(asteroid, generateAsteroidLinearVelocity(), generateAsteroidAngularVelocity());

    const Handle<SpriteRenderer>& renderer = asteroid->findComponent<SpriteRenderer>();

    addRectangleCollider(asteroid, renderer->getDimensions());

    m_asteroids.push_back(asteroid);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 AsteroidSpawningScript::generateAsteroidPosition() const
  {
    const glm::vec2& halfScreenDims = getViewportDimensions() * 0.5f;
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
    const glm::vec2& screenDimensions = getViewportDimensions();
    asteroidSpawner->getTransform()->translate(screenDimensions * 0.5f);

    addRectangleCollider(asteroidSpawner, screenDimensions);

    const Handle<AsteroidSpawningScript>& asteroidSpawning = asteroidSpawner->addComponent<kUnmanaged>(AsteroidSpawningScript::allocateAndInitialize());
    asteroidSpawning->setTinyAsteroidCount(tinyAsteroidCount);
    asteroidSpawning->setSmallAsteroidCount(smallAsteroidCount);
    asteroidSpawning->setLargeAsteroidCount(largeAsteroidCount);
    asteroidSpawning->setHugeAsteroidCount(hugeAsteroidCount);
  }
}