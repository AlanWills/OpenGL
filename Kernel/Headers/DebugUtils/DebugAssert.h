#pragma once

#include "DllExport.h"

namespace Kernel
{

/// Simple service class for providing customised runtime asserts
/// Using the service locator pattern in Debug we can change what Assert is registered and so provide extra functionality when it is needed
/// A good example of this is turning off Asserts in unit tests (cannot be done via macros it seems) by registering a NullAssert with Debug
class DllExport DebugAssert
{
  public:
    /// \brief This is the functionality of the assert
    /// Will check the inputted condition
    virtual void check(bool condition) const;
};

};