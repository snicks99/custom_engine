#ifndef STREAM_DEFINES_H
#define STREAM_DEFINES_H

#include "Common/Types.h"

enum StreamOpenMode : uint32
{
    STREAM_OPEN_READ  = 0x01,
    STREAM_OPEN_WRITE = 0x02,

    STREAM_OPEN_CREATE = 0x04,
    STREAM_OPEN_APPEND = 0x08,
};

enum StreamSeekType : uint32
{
    STREAM_SEEK_BEG = 0,
    STREAM_SEEK_CUR,
    STREAM_SEEK_END,
};

#endif
