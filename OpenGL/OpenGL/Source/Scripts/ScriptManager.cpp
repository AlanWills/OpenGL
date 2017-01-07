#include "stdafx.h"

#include "Scripts/ScriptManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ScriptManager::ScriptManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  ScriptManager::~ScriptManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  ScriptManager& ScriptManager::instance()
  {
    static ScriptManager scriptManager;

    return scriptManager;
  }
}