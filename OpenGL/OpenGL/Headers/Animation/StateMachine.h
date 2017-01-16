#pragma once

#include "Objects/Component.h"
#include "AnimationState.h"


namespace OpenGL
{

class StateMachine : public Component
{
  DECLARE_COMPONENT(PoolAllocator, StateMachine, 10);

  public:
    void update(GLfloat secondsPerUpdate) override;

    /// \brief Adds a new animation state into this state machine
    Handle<AnimationState> addState(const Handle<Animation>& animation);

    /// \brief Sets the current animstate to the inputted one
    /// This can only occur before awake() is called - from then on, the state machine has full control
    void setStartingState(const Handle<AnimationState>& animState);

  private:
    typedef Component Inherited;
    typedef std::vector<Handle<AnimationState>> States;
    typedef PoolAllocator<AnimationState, 10> StateAllocator;

    /// \brief Need to work out how to copy construct this
    StateAllocator m_stateAllocator;

    States m_states;

    Handle<AnimationState> m_currentAnimState;
};

}