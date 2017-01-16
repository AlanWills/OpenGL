#pragma once


#include <functional>


namespace OpenGL
{

class Transition
{
public:
  typedef std::function<bool()> TransitionFunc;

  Transition();

  //void setDestinationState(const Handle<AnimationState>& destinationAnimState);
  //const Handle<AnimationState>& getDestinationState() const { return m_destinationAnimState; }
  void setDestinationState(const std::string& stateName) { m_destinationStateName = stateName; }
  const std::string& getDestinationState() const { return m_destinationStateName; }

  void setTransitionFunction(const TransitionFunc& transitionFunc) { m_transitionFunc = transitionFunc; }

  /// \brief Invoke the transition function to test for successful transition
  bool testTransitionFunction() const;

private:

  /// \brief A function which we use to determine whether this transition should fire
  TransitionFunc m_transitionFunc;

  //Handle<AnimationState> m_destinationAnimState;
  std::string m_destinationStateName;
};

}