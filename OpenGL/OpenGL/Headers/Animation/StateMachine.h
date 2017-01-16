#pragma once

#include "Objects/Component.h"
#include "Animation.h"
#include "Transition.h"


namespace OpenGL
{

class StateMachine : public Component
{
  DECLARE_COMPONENT(PoolAllocator, StateMachine, 10);

  public:
    void update(GLfloat secondsPerUpdate) override;

    /// \brief Adds a new animation state into this state machine
    void addState(const Handle<Animation>& newAnimationState) { m_animations.push_back(newAnimationState); }

    /// \brief Create a new transition between the two inputted animation states
    /// The inputted function dicatates when the 'from' state should move to the 'to' state
    const Handle<Transition>& addTransition(
      const Handle<Animation>& from, 
      const Handle<Animation>& to,
      const Transition::TransitionFunc& transitionFunc);

    /// \brief Sets the current animstate to the inputted one
    /// This can only occur before awake() is called - from then on, the state machine has full control
    void setStartingAnimState(const Handle<Animation>& animState);

  private:
    typedef Component Inherited;
    typedef std::vector<Handle<Transition>> Transitions;
    typedef std::vector<Handle<Animation>> Animations;

    /// \brief Need to work out how to copy construct this without massive overhead
    PoolAllocator<Transition, 10> m_transitionAllocator;

    Transitions m_transitions;
    Animations m_animations;

    Handle<Animation> m_currentAnimState;
};

}