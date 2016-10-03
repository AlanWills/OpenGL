#pragma once

#include "DllExport.h"

namespace Engine
{

// A static class that is used to group various debugging tools together using the service locator pattern
// Contains: logger, profiler
class DebugManager
{
  private:
    DebugManager();
    ~DebugManager();
};

}