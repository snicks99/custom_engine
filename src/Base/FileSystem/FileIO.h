#ifndef FILE_IO_H
#define FILE_IO_H

#include "Common/ProjectConfig.h"

#if ENABLE_STL_FILE_SYSTEM

using FileHandle = FILE*;

#else

#    if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

using FileHandle = HANDLE;

#    elif DBL_PLATFORM == DBL_PLATFORM_UNIX

using FileHadle = int;

#    endif

#endif

enum class Disposition : uint8
{
    NONE = 0,
    CREATE, /**< only for [WRITE] mode */
    APPEND, /**< only for [WRITE] */
};

namespace FileIO
{
    FileHandle Open( const char8* filePath, uint32 mode, Disposition disposition );
    void       Close( FileHandle& fileHandle );

    bool8 Seek( FileHandle fileHandle, uint32 method, int64 offset = 0 );

    word_t Tell( FileHandle fileHandle );
    word_t Size( FileHandle fileHandle );

    word_t Read( FileHandle fileHandle, void* buffer, word_t length );
    word_t Write( FileHandle fileHandle, const void* buffer, word_t length );

    bool8 Exists( const char8* filePath );
};    // namespace FileIO

#endif
