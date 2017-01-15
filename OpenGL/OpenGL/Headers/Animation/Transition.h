#pragma once

#include "AnimationController.h"

#include <functional>


namespace OpenGL
{

class Transition
{
  public:
    typedef std::function<bool()> TransitionFunc;

    Transition();

    void setSourceState(const Handle<AnimationController>& sourceAnimState) { m_sourceAnimState = sourceAnimState; }

    void setDestinationState(const Handle<AnimationController>& destinationAnimState) { m_destinationAnimState = destinationAnimState; }
    const Handle<AnimationController>& getDestinationState() const { return m_destinationAnimState; }

    void setTransitionFunction(const TransitionFunc& transitionFunc) { m_transitionFunc = transitionFunc; }

    /// \brief Invoke the transition function for this transition to test for successful transition
    bool testTransitionFunction() const;

  private:

    /// \brief A function which we use to determine whether this transition should fire
    TransitionFunc m_transitionFunc;

    Handle<AnimationController> m_sourceAnimState;
    Handle<AnimationController> m_destinationAnimState;
};

}