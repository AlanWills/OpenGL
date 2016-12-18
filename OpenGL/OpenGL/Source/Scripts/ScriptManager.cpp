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
    for (const NameAllocatorPair& pair : m_scriptAllocators)
    {
      pair.second->~ComponentAllocator();
    }
  }

  //------------------------------------------------------------------------------------------------
  ScriptManager& ScriptManager::instance()
  {
    static ScriptManager scriptManager;

    return scriptManager;
  }
}