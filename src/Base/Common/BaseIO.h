#ifndef BASE_IO_H
#define BASE_IO_H

#include "Common/Types.h"

enum IOOpenMode : uint32
{
    IO_OPEN_READ  = 0x01,
    IO_OPEN_WRITE = 0x02,
};

enum IOSeekType : uint32
{
    IO_SEEK_BEG = 0,
    IO_SEEK_CUR,
    IO_SEEK_END,
};

#endif
