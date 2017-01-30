#include "stdafx.h"

#include "Levels/SpaceLevel.h"
#include "Game/GameManager.h"
#include "Scripts/AsteroidSpawningScript.h"
#include "Physics/RectangleCollider.h"


namespace OpenGL
{
  std::string SpaceLevel::m_backgroundNodeName = "BackgroundRelativeFilePath";
  std::string SpaceLevel::m_tinyAsteroidNodeName = "TinyAsteroidCount";
  std::string SpaceLevel::m_smallAsteroidNodeName = "SmallAsteroidCount";
  std::string SpaceLevel::m_largeAsteroidNodeName = "LargeAsteroidCount";
  std::string SpaceLevel::m_hugeAsteroidNodeName = "HugeAsteroidCount";

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::load(const Handle<Screen>& screen, const Path& relativeDataFilePath)
  {
    const glm::vec2& screenDimensions = GameManager::getScreenManager()->getViewportDimensions();

    const Handle<Data>& levelData = GameManager::getResourceManager()->loadData(relativeDataFilePath.as_string());
    ASSERT(levelData.get());

    addBackground(screen, levelData->getNodeDataAsText(m_backgroundNodeName));

    addAsteroidSpawningScript(
      screen,
      levelData->getNodeDataAsFloat(m_tinyAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_smallAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_largeAsteroidNodeName),
      levelData->getNodeDataAsFloat(m_hugeAsteroidNodeName));
  }
}