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
  void SpaceLevel::load(const Path& relativeDataFilePath, const Handle<Screen>& screen)
  {
    const glm::vec2& screenDimensions = GameManager::getScreenManager()->getViewportDimensions();

    const Handle<Data>& levelData = GameManager::getResourceManager()->loadData(relativeDataFilePath.as_string());
    ASSERT(levelData.get());

    // TODO: Put this in a header file with lots of utilities for screen stuff in the OpenGL namespace
    // It's also drawn in front cos it's UI - need to move it to the back
    // Can we also have a utility function for setting a texture to respect it's aspect ratio
    const Handle<Image>& image = screen->getUIManager().allocateAndInitializeImage();
    {
      image->setImage(levelData->getNodeDataAsText(m_backgroundNodeName));
      image->setSize(screenDimensions);
      image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));
    }

    // TODO: Put this in the script header file as a global function in the OpenGL namespace for adding to a screen
    const Handle<GameObject>& asteroidSpawner = screen->allocateAndInitializeGameObject();
    {
      asteroidSpawner->getTransform()->translate(screenDimensions * 0.5f);

      const Handle<RectangleCollider>& asteroidCollider = asteroidSpawner->addComponent<kManaged>(RectangleCollider::allocateAndInitialize());
      asteroidCollider->setDimensions(screenDimensions);

      const Handle<AsteroidSpawningScript>& asteroidSpawning = asteroidSpawner->addComponent<kUnmanaged>(AsteroidSpawningScript::allocateAndInitialize());
      asteroidSpawning->setTinyAsteroidCount(levelData->getNodeDataAsFloat(m_tinyAsteroidNodeName));
      asteroidSpawning->setSmallAsteroidCount(levelData->getNodeDataAsFloat(m_smallAsteroidNodeName));
      asteroidSpawning->setLargeAsteroidCount(levelData->getNodeDataAsFloat(m_largeAsteroidNodeName));
      asteroidSpawning->setHugeAsteroidCount(levelData->getNodeDataAsFloat(m_hugeAsteroidNodeName));
    }
  }
}