#include "stdafx.h"

#include "Levels/SpaceLevel.h"
#include "Resources/ResourceManager.h"
#include "Scripts/AsteroidSpawningScript.h"
#include "Physics/RectangleCollider.h"
#include "Viewport/Camera.h"


namespace Game
{
  std::string SpaceLevel::m_backgroundNodeName = "BackgroundRelativeFilePath";
  std::string SpaceLevel::m_tinyAsteroidNodeName = "TinyAsteroidCount";
  std::string SpaceLevel::m_smallAsteroidNodeName = "SmallAsteroidCount";
  std::string SpaceLevel::m_largeAsteroidNodeName = "LargeAsteroidCount";
  std::string SpaceLevel::m_hugeAsteroidNodeName = "HugeAsteroidCount";
  std::string SpaceLevel::m_levelBoundsNodeName = "LevelBounds";
  std::string SpaceLevel::m_spawnPointsNodeName = "SpawnPoints";

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::load(const Handle<Screen>& screen, const Path& relativeDataFilePath)
  {
    const glm::vec2& screenDimensions = getViewportDimensions();

    const Handle<Data>& levelData = getResourceManager()->loadData(relativeDataFilePath.as_string());
    ASSERT(levelData.get());

    // Add the background image corresponding to the image in the data file
    addStaticBackground(screen, levelData->getElementDataAsText(m_backgroundNodeName));

    // Add asteroids with densities corresponding to the values in the data file
    createAsteroids(screen, levelData);

    // Add a game object which holds the bounds of the level
    createLevelBounds(screen, levelData);

    // Add the spawn points in the locations described in the data file
    createSpawnPoints(screen, levelData);
  }

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::createAsteroids(const Handle<Screen>& screen, const Handle<Data>& levelData)
  {
    const Handle<CelesteEngine::GameObject>& asteroidSpawner = screen->allocateGameObject();
    createAsteroidSpawner(
      asteroidSpawner,
      levelData->getElementDataAsFloat(m_tinyAsteroidNodeName),
      levelData->getElementDataAsFloat(m_smallAsteroidNodeName),
      levelData->getElementDataAsFloat(m_largeAsteroidNodeName),
      levelData->getElementDataAsFloat(m_hugeAsteroidNodeName));

    // Attach to camera so the asteroids are invariant of the camera position
    attachToCamera(asteroidSpawner);
  }

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::createLevelBounds(const Handle<Screen>& screen, const Handle<Data>& levelData)
  {
    const XMLElement* levelBoundsElement = levelData->getElement(m_levelBoundsNodeName);

    float width = 0, height = 0;

    levelBoundsElement->QueryFloatAttribute("width", &width);
    levelBoundsElement->QueryFloatAttribute("height", &height);

    const Handle<CelesteEngine::GameObject>& levelBounds = screen->allocateGameObject();
    addRectangleCollider(levelBounds, glm::vec2(width, height));
    levelBounds->setName("LevelBounds");
  }

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::createSpawnPoints(const Handle<Screen>& screen, const Handle<Data>& levelData)
  {
    const XMLNode* spawnPoints = levelData->getElement(m_spawnPointsNodeName);
    if (!spawnPoints->NoChildren())
    {
      for (const XMLElement* child = spawnPoints->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
      {
        float x = 0, y = 0;

        child->QueryFloatAttribute("x", &x);
        child->QueryFloatAttribute("y", &y);

        const Handle<CelesteEngine::GameObject>& spawnPoint = screen->allocateGameObject();
        spawnPoint->getTransform()->setTranslation(x, y, 1);
        spawnPoint->setTag("SpawnPoint");

        createSprite(spawnPoint, child->GetText());
      }
    }
  }
}