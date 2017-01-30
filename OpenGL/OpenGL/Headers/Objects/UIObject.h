#pragma once

#include "GameObject.h"


namespace OpenGL
{

class UIObject : public GameObject
{
  public:
    UIObject();
    ~UIObject();

    void initialize(const Handle<Component>& allocHandle) override;

  private:
    typedef GameObject Inherited;
};

}