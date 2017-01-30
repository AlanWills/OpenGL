#include "stdafx.h"

#include "Levels/SpaceLevel.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  std::string SpaceLevel::m_backgroundNodeName = "BackgroundRelativeFilePath";

  //------------------------------------------------------------------------------------------------
  void SpaceLevel::load(const Path& relativeDataFilePath, const Handle<Screen>& screen)
  {
    const glm::vec2& screenDimensions = GameManager::getScreenManager()->getViewportDimensions();

    const Handle<Data>& levelData = GameManager::getResourceManager()->loadData(relativeDataFilePath.as_string());
    ASSERT(levelData.get());

    const char* backgroundRelativeFilePath = levelData->getNodeText(m_backgroundNodeName);
    ASSERT(backgroundRelativeFilePath);

    Handle<Image> image = screen->getUIManager().allocateAndInitializeImage();
    image->setImage(backgroundRelativeFilePath);
    image->setSize(screenDimensions);
    image->getTransform()->translate(glm::vec3(screenDimensions * 0.5f, 0));
  }
}