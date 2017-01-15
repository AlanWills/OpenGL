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
  DECLARE_COMPONENT(PoolAllocator, MouseInteractionHandler, 10);

  public:
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;

    /// \brief An event that will be called when the mouse first enters the parent's collider
    EVENT_FUNCTIONS(Enter, GameObjectClickCallback)

    /// \brief An event that will be called when the mouse first leaves the parent's collider
    EVENT_FUNCTIONS(Leave, GameObjectClickCallback)

    /// \brief An event that will be called when the parent's collider is left clicked using the mouse
    EVENT_FUNCTIONS(LeftClick, GameObjectClickCallback)

    /// \brief An event that will be called when the parent's collider is left clicked using the mouse
    EVENT_FUNCTIONS(MiddleClick, GameObjectClickCallback)

    /// \brief An event that will be called when the parent's collider is left clicked using the mouse
    EVENT_FUNCTIONS(RightClick, GameObjectClickCallback)

  private:
    typedef Component Inherited;
    typedef Event<Handle<GameObject>> GameObjectEvent;

    GameObjectEvent m_onEnter;
    GameObjectEvent m_onLeave;
    GameObjectEvent m_onLeftClick;
    GameObjectEvent m_onMiddleClick;
    GameObjectEvent m_onRightClick;

    Handle<Collider> m_collider;
    bool m_isMouseOver;
};

}