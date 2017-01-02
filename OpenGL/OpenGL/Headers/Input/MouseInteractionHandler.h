#pragma once

#include "Objects/Component.h"

class Button;


namespace OpenGL
{

class MouseInteractionHandler : public Component
{
  DECLARE_COMPONENT(MouseInteractionHandler, 10);

  public:
    typedef void(Button::* ClickHandler)();

    /// \brief Add a function to execute when we left click on the object this is associated with
    void addOnLeftClickEvent(ClickHandler onLeftClick) { m_onLeftClick = onLeftClick; }

    void test();

  private:
    ClickHandler m_onLeftClick;
};

}