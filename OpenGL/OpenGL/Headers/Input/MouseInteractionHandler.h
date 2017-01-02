#pragma once

#include "Objects/Component.h"
#include "Events/Event.h"
#include "Physics/Collider.h"

class GameObject;


namespace OpenGL
{

#define EVENT_FUNCTIONS(Name, CallbackType) \
  public: \
    void addOn##Name##Event(const CallbackType& on##Name) { m_on##Name##.subscribe(on##Name); } \
    void removeOn##Name##Event(const CallbackType& on##Name) { m_on##Name##.unsubscribe(on##Name); }
    

typedef std::function<void(Handle<GameObject>)> GameObjectClickCallback;

class MouseInteractionHandler : public Component
{
  DECLARE_COMPONENT(MouseInteractionHandler, 10);

  public:
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;

    /// \brief An event that will be called when the mouse first enters the parent's collider
    EVENT_FUNCTIONS(Enter, GameObjectClickCallback)

    /// \brief An event that will be called when the mouse first leaves the parent's collider
    EVENT_FUNCTIONS(Leave, GameObjectClickCallback)

  private:
    typedef Component Inherited;

    Event<void, Handle<GameObject>> m_onEnter;
    Event<void, Handle<GameObject>> m_onLeave;

    Handle<Collider> m_collider;
    bool m_isMouseOver;
};

}