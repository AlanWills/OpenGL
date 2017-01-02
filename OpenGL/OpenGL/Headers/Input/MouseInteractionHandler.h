#pragma once

#include "Objects/Component.h"
#include "Events/Event.h"

class GameObject;


namespace OpenGL
{

typedef std::function<void(GameObject)> GameObjectClickCallback;

class MouseInteractionHandler : public Component
{
  DECLARE_COMPONENT(MouseInteractionHandler, 10);

  public:
    /// \brief Add a function to execute when we left click on the object this is associated with
    void addOnLeftClickEvent(const GameObjectClickCallback& onLeftClick) { m_onLeftClick.subscribe(onLeftClick); }
    void removeOnLeftClickEvent(const GameObjectClickCallback& onLeftClick) { m_onLeftClick.unsubscribe(onLeftClick); }

  private:
    Event<void, GameObject> m_onLeftClick;
};

}