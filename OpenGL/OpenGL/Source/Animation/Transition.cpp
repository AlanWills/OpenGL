#include "stdafx.h"

#include "Animation/Transition.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Transition::Transition() :
    m_sourceAnimState(nullptr),
    m_destinationAnimState(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Transition::testTransitionFunction() const
  {
    // Our source state can be null (global transition), but our destination state cannot be
    ASSERT(m_destinationAnimState.get());

    // The transition func cannot be nullptr either
    return m_transitionFunc();
  }
}