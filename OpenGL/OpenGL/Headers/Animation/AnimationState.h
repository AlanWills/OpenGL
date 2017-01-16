#pragma once

#include "Objects/Component.h"
#include "Animation.h"

#include <functional>
#include <unordered_map>


namespace OpenGL
{

class AnimationState : public Component
{
  public:
    typedef std::function<bool()> TransitionFunc;
    typedef std::unordered_map<Handle<AnimationState>, TransitionFunc> Transitions;
    typedef std::pair<Handle<AnimationState>, TransitionFunc> Transition;

    AnimationState();
    virtual ~AnimationState();

    void awake() override;

    /// \brief Create a new transition between the two inputted animation states
    /// The inputted function dicatates when the 'from' state should move to the 'to' state
    void addTransition(
      const Handle<AnimationState>& to,
      const TransitionFunc& transitionFunc);

    void setAnimation(const Handle<Animation>& animation);

    /// \brief Resumes and restarts the animation
    void startAnimation();

    /// \brief Pauses and restarts the animation
    void stopAnimation();

    Transitions::const_iterator begin() const { return m_transitions.begin(); }
    Transitions::const_iterator end() const { return m_transitions.end(); }

  private:
    typedef Component Inherited;

    Transitions m_transitions;

    Handle<Animation> m_animation;
};

}