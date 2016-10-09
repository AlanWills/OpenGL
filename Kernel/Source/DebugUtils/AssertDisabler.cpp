#include "DebugUtils/AssertDisabler.h"
#include "DebugUtils/Debug.h"

using namespace Kernel;

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  AssertDisabler::AssertDisabler()
  {
    Debug::setAssert(new NullAssert());
  }

  //------------------------------------------------------------------------------------------------
  AssertDisabler::~AssertDisabler()
  {
    Debug::setAssert(new DebugAssert());
  }
}