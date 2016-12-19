#pragma once

#include "Objects/Component.h"
#include "Memory/ComponentAllocator.h"
#include "StringInterning/StringId.h"

using namespace Kernel;


namespace OpenGL
{
//------------------------------------------------------------------------------------------------
#define DECLARE_SCRIPT(ScriptType, PoolSize) \
public: \
  static bool canAllocate() { return m_scriptAllocator.canAllocate(); } \
  static ScriptType* allocate() { return m_scriptAllocator.allocate(); } \
  static ScriptType* allocateAndInitialize() \
  { \
    ASSERT(m_scriptAllocator.canAllocate()); \
    ScriptType* script = m_scriptAllocator.allocate(); \
    script->initialize(); \
    return script; \
  } \
private: \
  typedef ComponentAllocator<ScriptType, PoolSize> ScriptAllocator; \
  static ComponentAllocator<ScriptType, PoolSize> m_scriptAllocator;

//------------------------------------------------------------------------------------------------
#define REGISTER_SCRIPT(ScriptType, ScriptName) \
ScriptType::ScriptAllocator ScriptType::m_scriptAllocator = ScriptType::ScriptAllocator();


//------------------------------------------------------------------------------------------------
class Script : public Component
{
  public:
    Script();
    virtual ~Script();

  private:
    typedef Component Inherited;
};

}