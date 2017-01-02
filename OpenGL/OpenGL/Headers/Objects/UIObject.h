#pragma once

#include "GameObject.h"


namespace OpenGL
{

class UIObject : public GameObject
{
  public:
    UIObject();
    virtual ~UIObject();

    void initialize(Handle<Component> allocHandle) override;

  private:
    typedef Component Inherited;
};

}