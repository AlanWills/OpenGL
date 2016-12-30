#pragma once

#include "Objects/GameObject.h"


namespace OpenGL
{

class Button : public GameObject
{
  DECLARE_COMPONENT_WITH_MANAGER(Button, 10, UIManager);
};

}