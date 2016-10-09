#pragma once

#include "DllExport.h"


namespace Kernel
{

/// A simple class which attaches a NullAssert to Debug in it's constructor and then attaches a DebugAssert in it's destructor
/// This means that in it's lifetime Asserts do not fire
class DllExport AssertDisabler
{
  public:
    AssertDisabler();
    ~AssertDisabler();
};

};