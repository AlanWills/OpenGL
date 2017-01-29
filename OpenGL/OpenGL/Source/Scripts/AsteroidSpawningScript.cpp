#include "stdafx.h"

#include "Scripts/AsteroidSpawningScript.h"
#include "Game/GameManager.h"
#include "Physics/RigidBody2D.h"

#include <random>


namespace OpenGL
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
    m_hugeAsteroidCount(0)
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

    // Seed the random generator
    srand(time(nullptr));

    ASSERT(getParent().get());
    m_bounds = getParent()->findComponent<RectangleCollider>();
    ASSERT(m_bounds.get());

    createAsteroids();
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
    const Handle<Screen>& currentScreen = GameManager::getScreenManager()->getCurrentScreen();
    
    if (!currentScreen->canAllocateGameObject())
    {
      ASSERT_FAIL("Out of game objects.  Consider increasing pool size");
      return;
    }

    Handle<GameObject> asteroid = currentScreen->allocateAndInitializeGameObject();
    asteroid->getTransform()->setParent(getParent()->getTransform());
    asteroid->getTransform()->setTranslation(glm::vec3(generateAsteroidPosition(), 0));

    if (!SpriteRenderer::canAllocate())
    {
      ASSERT_FAIL("Out of SpriteRenderers.  Consider increasing pool size");
      return;
    }

    Handle<SpriteRenderer> renderer = asteroid->addComponent<kManaged>(SpriteRenderer::allocateAndInitialize());
    renderer->setTexture(asteroidTexturePath.as_string());

    if (!RigidBody2D::canAllocate())
    {
      ASSERT_FAIL("Out of RigidBody2Ds.  Consider increasing pool size");
      return;
    }

    Handle<RigidBody2D> rigidBody = asteroid->addComponent<kManaged>(RigidBody2D::allocateAndInitialize());
    rigidBody->setLinearVelocity(generateAsteroidLinearVelocity());
    rigidBody->setAngularVelocity(generateAsteroidAngularVelocity());

    m_asteroids.push_back(asteroid);
  }
}