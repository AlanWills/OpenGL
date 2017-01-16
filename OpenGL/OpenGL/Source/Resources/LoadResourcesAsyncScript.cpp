#include "stdafx.h"

#include "Resources/LoadResourcesAsyncScript.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(LoadResourcesAsyncScript)

  //------------------------------------------------------------------------------------------------
  LoadResourcesAsyncScript::LoadResourcesAsyncScript() :
    m_timeElapsed(0)/*,
    m_loadingThread(nullptr)*/
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

    //m_loadingThread = new std::thread(std::function<void()>(std::bind(&ResourceManager::initialize, GameManager::getResourceManager())));
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_timeElapsed += secondsPerUpdate;

    if (/*m_loadingThread->joinable() &&*/ m_timeElapsed > MIN_WAIT_TIME)
    {
      GameManager::getScreenManager()->getScreenFactory()->transitionToMainMenuScreen();
    }
  }

  //------------------------------------------------------------------------------------------------
  void LoadResourcesAsyncScript::die()
  {
    Inherited::die();

    //if (m_loadingThread)
    {
      // Delete our allocated thread
      //delete m_loadingThread;
    }
  }
}