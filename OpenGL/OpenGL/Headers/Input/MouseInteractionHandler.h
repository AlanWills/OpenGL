#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

class MouseInteractionHandler : public Component
{
  DECLARE_COMPONENT(MouseInteractionHandler, 10);

  public:
    MouseInteractionHandler();
    ~MouseInteractionHandler();

    typedef void(*ClickHandler)();

    /// \brief Set the function to execute when we left click on the object this is associated with
    void setOnLeftClick(ClickHandler onLeftClick) { m_onLeftClick = onLeftClick; }

  private:
    ClickHandler m_onLeftClick;
};

}