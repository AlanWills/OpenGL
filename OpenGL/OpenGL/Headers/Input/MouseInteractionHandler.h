#pragma once

#include "Objects/Component.h"
#include <functional>

class GameObject;


namespace OpenGL
{

typedef std::function<void(Handle<GameObject>)> ClickEvent;

class MouseInteractionHandler : public Component
{
  DECLARE_COMPONENT(MouseInteractionHandler, 10);

  public:
    /// \brief Add a function to execute when we left click on the object this is associated with
    void addOnLeftClickEvent(const ClickEvent& onLeftClick) { m_onLeftClick = onLeftClick; }

  private:
    ClickEvent m_onLeftClick;
};

}