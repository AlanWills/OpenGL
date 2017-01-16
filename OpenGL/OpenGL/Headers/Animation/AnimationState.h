#pragma once

#include "Objects/Component.h"
#include "Animation.h"
#include "Transition.h"

#include <functional>


namespace OpenGL
{

class AnimationState : public Component
{
private:
  typedef std::vector<Handle<Transition>> Transitions;

public:
  AnimationState();
  virtual ~AnimationState();

  void awake() override;

  /// \brief Create a new transition between the two inputted animation states
  /// The inputted function dicatates when the 'from' state should move to the 'to' state
  Handle<Transition> addTransition(
    const Handle<AnimationState>& to,
    const Transition::TransitionFunc& transitionFunc);

  void setAnimation(const Handle<Animation>& animation);

  /// \brief Resumes and restarts the animation
  void startAnimation();

  /// \brief Pauses and restarts the animation
  void stopAnimation();

  Transitions::const_iterator begin() const { return m_transitions.begin(); }
  Transitions::const_iterator end() const { return m_transitions.end(); }

private:
  typedef Component Inherited;
  typedef PoolAllocator<Transition, 10> TransitionAllocator;

  /// \brief Need to work out how to copy construct this without massive overhead
  TransitionAllocator m_transitionAllocator;

  Transitions m_transitions;

  Handle<Animation> m_animation;
};

}