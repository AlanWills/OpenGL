#include "stdafx.h"

#include "Scripts/AsteroidSpawningScript.h"
#include "Game/GameManager.h"
#include "Physics/RigidBody2D.h"


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

    for (const Handle<GameObject>& asteroid : m_asteroids)
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
    const Handle<Screen>& currentScreen = GameManager::getScreenManager()->getCurrentScreen();
    
    if (!currentScreen->canAllocateGameObject())
    {
      ASSERT_FAIL("Out of game objects.  Consider increasing pool size");
      return;
    }

    const Handle<GameObject>& asteroid = currentScreen->allocateAndInitializeGameObject();
    asteroid->getTransform()->setParent(getParent()->getTransform());
    asteroid->getTransform()->setTranslation(glm::vec3(generateAsteroidPosition(), 0));

    if (!SpriteRenderer::canAllocate())
    {
      ASSERT_FAIL("Out of SpriteRenderers.  Consider increasing pool size");
      return;
    }

    const Handle<SpriteRenderer>& renderer = asteroid->addComponent<kManaged>(SpriteRenderer::allocateAndInitialize());
    renderer->setTexture(asteroidTexturePath.as_string());

    if (!RigidBody2D::canAllocate())
    {
      ASSERT_FAIL("Out of RigidBody2Ds.  Consider increasing pool size");
      return;
    }

    const Handle<RigidBody2D>& rigidBody = asteroid->addComponent<kManaged>(RigidBody2D::allocateAndInitialize());
    rigidBody->setLinearVelocity(generateAsteroidLinearVelocity());
    rigidBody->setAngularVelocity(generateAsteroidAngularVelocity());

    const Handle<RectangleCollider>& collider = asteroid->addComponent<kManaged>(RectangleCollider::allocateAndInitialize());
    collider->setDimensions(renderer->getDimensions());

    m_asteroids.push_back(asteroid);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec2 AsteroidSpawningScript::generateAsteroidPosition() const
  {
    const glm::vec2& halfScreenDims = GameManager::getScreenManager()->getViewportDimensions() * 0.5f;
    return glm::vec2(m_random.generate(-halfScreenDims.x, halfScreenDims.x), m_random.generate(-halfScreenDims.y, halfScreenDims.y));
  }
}