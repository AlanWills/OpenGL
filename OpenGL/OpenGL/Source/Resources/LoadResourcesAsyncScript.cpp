#include "stdafx.h"

#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(LoadResourcesAsyncScript)

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::LoadResourcesAsyncScript() :
    m_loadingThread(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::~LoadResourcesAsyncScript()
  {
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::awake()
  {
    Inherited::awake();

    m_loadingThread = new std::thread(std::function<void()>(std::bind(&ResourceManager::initialize, GameManager::getResourceManager())));
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    if (m_loadingThread->joinable())
    {
      GameManager::getScreenManager()->transitionToScreen(Screen::allocateAndInitialize());
    }
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::die()
  {
    Inherited::die();

    if (m_loadingThread)
    {
      // Delete our allocated thread
      delete m_loadingThread;
    }
  }
}