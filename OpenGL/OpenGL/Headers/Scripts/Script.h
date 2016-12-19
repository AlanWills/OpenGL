#pragma once

#include "Objects/Component.h"
#include "Memory/ComponentAllocator.h"
#include "StringInterning/StringId.h"

using namespace Kernel;


namespace OpenGL
{

  class Script : public Component
{
  public:
    Script();
    virtual ~Script();

  private:
    typedef Component Inherited;
};

}