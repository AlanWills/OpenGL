#include "DebugUtils/DebugAssert.h"
#include <assert.h>


namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void DebugAssert::check(bool condition) const
  {
    assert(condition);
  }
}