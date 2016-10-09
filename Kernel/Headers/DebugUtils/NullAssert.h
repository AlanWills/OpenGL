#pragma once

#include "Assert.h"

namespace Kernel
{

/// Assert class designed to not do any debug checking - useful for when we wish to temporarily disable asserts in tests for example
class DllExport NullAssert : public DebugAssert
{
  /// \brief No-op check function
  void check(bool condition) const override { /* No-op */ }
};

};