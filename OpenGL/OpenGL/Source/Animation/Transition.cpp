#include "stdafx.h"

#include "Animation/Transition.h"
#include "Animation/AnimationState.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Transition::Transition() :
    m_destinationStateName("")
  {
  }

  //------------------------------------------------------------------------------------------------
  /*void Transition::setDestinationState(const std::string& destinationAnimState)
  {
    m_destinationStateName = destinationAnimState;
  }*/

  //------------------------------------------------------------------------------------------------
  bool Transition::testTransitionFunction() const
  {
    // Our destination state cannot be empty
    ASSERT(!m_destinationStateName.empty());

    // The transition func cannot be nullptr either
    return m_transitionFunc();
  }
}