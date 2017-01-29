#pragma once

#include "GameObject.h"


namespace OpenGL
{

class UIObject : public GameObject
{
  public:
    UIObject();
    virtual ~UIObject();

  private:
    typedef GameObject Inherited;
};

}