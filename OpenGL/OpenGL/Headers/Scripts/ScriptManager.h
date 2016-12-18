#pragma once

#include "Script.h"
#include "Memory/ComponentAllocator.h"

#include <unordered_map>


namespace OpenGL
{

class ScriptManager : public Component
{
  #define SCRIPTMANAGER_POOL_SIZE 10

  public:
    ScriptManager();
    virtual ~ScriptManager();

    static ScriptManager& instance();

    template <typename T>
    bool registerScript(StringId scriptName);

    template <typename T>
    T* allocateScript();

    template <typename T>
    T* allocateAndInitializeScript();

  private:
    typedef Component Inherited;
    typedef ComponentAllocator<Script, SCRIPTMANAGER_POOL_SIZE> ScriptAllocator;
    typedef std::pair<StringId, ScriptAllocator*> NameAllocatorPair;
    typedef std::unordered_map<StringId, ScriptAllocator*> ScriptAllocatorMap;

    ScriptAllocatorMap m_scriptAllocators;
};


//------------------------------------------------------------------------------------------------
template <typename T>
bool ScriptManager::registerScript(StringId scriptName)
{
  if (m_scriptAllocators.find(scriptName) != m_scriptAllocators.end())
  {
    ASSERT_FAIL();
    return false;
  }

  NameAllocatorPair pair;
  pair.first = scriptName;
  pair.second = new ScriptAllocator();

  m_scriptAllocators.insert(pair);

  return true;
}

//------------------------------------------------------------------------------------------------
template <typename T>
T* ScriptManager::allocateScript()
{
  StringId scriptName = T::getScriptName();

  if (m_scriptAllocators.find(scriptName) == m_scriptAllocators.end())
  {
    ASSERT_FAIL();
    return nullptr;
  }

  ScriptAllocator* allocator = m_scriptAllocators.at(scriptName);

  if (!allocator->canAllocate())
  {
    ASSERT_FAIL_MSG("Run out of scripts, consider increasing pool size");
    return nullptr;
  }

  return allocator->allocate()
}

//------------------------------------------------------------------------------------------------
template <typename T>
T* ScriptManager::allocateAndInitializeScript()
{
  T* script = allocateScript<T>();

  if (!script)
  {
    ASSERT_FAIL_MSG("Script is nullptr");
    return nullptr;
  }

  script->initialize();

  return script;
}

}