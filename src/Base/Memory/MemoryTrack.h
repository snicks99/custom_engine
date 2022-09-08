#ifndef MEMORY_TRACK_H
#define MEMORY_TRACK_H

#include "Common/Platform.h"

CONSTEXPR_INLINE word_t MAGIC_HEAP{ 0xAAAAAAAA };

struct MemoryTrack
{
  public:
    MemoryTrack()
        : mSize{ 0 }
        , mMagic{ MAGIC_HEAP }
    {
    }

    word_t mSize;
    word_t mMagic;
};

#endif
