#pragma once

namespace Engine
{

class AlignedAllocator
{
  public:
    AlignedAllocator();
    ~AlignedAllocator();

    // Have templated version too?
    void* allocateUnaligned(unsigned int numberOfBytes) const;

    /// \brief Alignment must be a power of 2
    void* allocateAligned(unsigned int numberOfBytes, unsigned int alignment) const;
};

};