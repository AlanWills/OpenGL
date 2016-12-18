#pragma once

#include "Objects/Component.h"
#include "StringInterning/StringId.h"

using namespace Kernel;


namespace OpenGL
{
#define DECLARE_SCRIPT() \
public: \
  static StringId getScriptName() { return m_scriptName; } \
  static StringId m_scriptName; \
  static bool m_b;

#define REGISTER_SCRIPT(ScriptType, ScriptName) \
StringId ScriptType::m_scriptName(internString(ScriptName)); \
bool ScriptType::m_b(ScriptManager::instance().registerScript<ScriptType>(internString(ScriptName)));


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