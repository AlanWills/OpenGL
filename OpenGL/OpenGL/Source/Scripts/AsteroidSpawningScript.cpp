#include "stdafx.h"

#include "Scripts/AsteroidSpawningScript.h"


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

    ASSERT(getParent().get());
    m_bounds = getParent()->findComponent<Collider>();
    ASSERT(m_bounds.get());
  }
}