#pragma once

#include "DllExport.h"

namespace Engine
{

template <typename T, size_t PoolSize>
class DllExport PoolAllocator
{
};

};

// Make this class templated and store a big array of objects and do degragmentation and all the stuff described in GEA
// Call constructor of all pooled objects at start