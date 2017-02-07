#pragma once

#include "Objects/Component.h"


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