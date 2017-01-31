#include "stdafx.h"

#include "Levels/SpaceLevel.h"
#include "Resources/ResourceManager.h"
#include "Scripts/AsteroidSpawningScript.h"
#include "Physics/RectangleCollider.h"
#include "Viewport/Camera.h"


namespace OpenGL
{
  std::string SpaceLevel::m_backgroundNodeName = "BackgroundRelativeFilePath";
  std::string SpaceLevel::m_tinyAsteroidNodeName = "TinyAsteroidCount";
  std::string SpaceLevel::m_smallAsteroidNodeName = "SmallAsteroidCount";
  std::string SpaceLevel::m_largeAsteroidNodeName = "LargeAsteroidCount";
  std::string SpaceLevel::m_hugeAsteroidNodeName = "HugeAsteroidCount";
  std::string SpaceLevel::m_spawnPoints = "SpawnPoints";

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::load(const Handle<Screen>& screen, const Path& relativeDataFilePath)
  {
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<Data>& levelData = getResourceManager()->loadData(relativeDataFilePath.as_string());
    ASSERT(levelData.get());

    // Add the background image corresponding to the image in the data file
    addBackground(screen, levelData->getNodeDataAsText(m_backgroundNodeName));

    // Add asteroids with densities corresponding to the values in the data file
    const Handle<GameObject>& asteroidSpawner = screen->allocateAndInitializeGameObject();
    createAsteroidSpawner(
      asteroidSpawner,
      levelData->getNodeDataAsFloat(m_tinyAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_smallAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_largeAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_hugeAsteroidNodeName));

    // Attach to camera so the asteroids are invariant of the camera position
    attachToCamera(asteroidSpawner);

    const XMLNode* spawnPoints = levelData->getNode(m_spawnPoints);
    if (!spawnPoints->NoChildren())
    {
      for (const XMLElement* child = spawnPoints->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
      {
        float x = 0, y= 0;

        child->QueryFloatAttribute("x", &x);
        child->QueryFloatAttribute("y", &y);

        const Handle<GameObject>& navBuoy = screen->allocateAndInitializeGameObject();
        navBuoy->getTransform()->translate(x, y, 1);

        createSprite(navBuoy, Path("Sprites", "Stations", "NavBuoy.png"));
      }
    }
  }
}