#pragma once

#include "Script.h"
#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "FileSystem/Path.h"
#include "Maths/RandomGenerator.h"


namespace OpenGL
{

class AsteroidSpawningScript : public Script
{
  DECLARE_COMPONENT(GapAllocator, AsteroidSpawningScript, 2);

  public:
    void awake() override;

    void setTinyAsteroidCount(int tinyAsteroidCount) { m_tinyAsteroidCount = tinyAsteroidCount; }
    void setSmallAsteroidCount(int smallAsteroidCount) { m_smallAsteroidCount = smallAsteroidCount; }
    void setLargeAsteroidCount(int largeAsteroidCount) { m_largeAsteroidCount = largeAsteroidCount; }
    void setHugeAsteroidCount(int hugeAsteroidCount) { m_hugeAsteroidCount = hugeAsteroidCount; }

  private:
    typedef Script Inherited;

    void createAsteroids();
    void createAsteroid(const Path& asteroidTexturePath);

    glm::vec2 generateAsteroidPosition() const;
    glm::vec2 generateAsteroidLinearVelocity() const { return glm::vec2(m_random.generate(0, 100), 0); }
    float generateAsteroidAngularVelocity() const { return m_random.generate(-0.5f, 0.5f); }

    std::vector<Handle<GameObject>> m_asteroids;

    /// \brief The bounds of this script's parent, which we will use to determine when asteroids have left the area
    Handle<RectangleCollider> m_bounds;

    int m_tinyAsteroidCount;
    int m_smallAsteroidCount;
    int m_largeAsteroidCount;
    int m_hugeAsteroidCount;

    static Path m_tinyAsteroidTexturePath;
    static Path m_smallAsteroidTexturePath;
    static Path m_largeAsteroidTexturePath;
    static Path m_hugeAsteroidTexturePath;

    RandomGenerator m_random;
};

}