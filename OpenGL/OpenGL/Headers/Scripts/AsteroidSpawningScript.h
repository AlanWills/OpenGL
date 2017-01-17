#pragma once

#include "Script.h"
#include "Objects/GameObject.h"
#include "Physics/Collider.h"
#include "FileSystem/Path.h"


namespace OpenGL
{

class AsteroidSpawningScript : public Script
{
  DECLARE_COMPONENT(GapAllocator, AsteroidSpawningScript, 2);

  public:
    void awake() override;

    void setTinyAsteroidCount(int tinyAsteroidCount) { m_tinyAsteroidCount = tinyAsteroidCount; }
    void setSmallAsteroidCount(int smallAsteroidCount) { m_tinyAsteroidCount = smallAsteroidCount; }
    void setLargeAsteroidCount(int largeAsteroidCount) { m_tinyAsteroidCount = largeAsteroidCount; }
    void setHugeAsteroidCount(int hugeAsteroidCount) { m_tinyAsteroidCount = hugeAsteroidCount; }

  private:
    typedef Script Inherited;

    std::vector<Handle<GameObject>> m_asteroids;

    /// \brief The bounds of this script's parent, which we will use to determine when asteroids have left the area
    Handle<Collider> m_bounds;

    int m_tinyAsteroidCount;
    int m_smallAsteroidCount;
    int m_largeAsteroidCount;
    int m_hugeAsteroidCount;

    static Path m_tinyAsteroidTexturePath;
    static Path m_smallAsteroidTexturePath;
    static Path m_largeAsteroidTexturePath;
    static Path m_hugeAsteroidTexturePath;
};

}