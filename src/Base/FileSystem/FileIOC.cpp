#include "FileSystem/FileIO.h"
#include "Debug/MGEAssert.h"

#if ENABLE_STL_FILE_SYSTEM

namespace FileIO
{

    const char8* GetOpenMode( uint32 mode )
    {
        if ( mode & READ )
        {
            if ( mode & WRITE )
            {
                return "r+b";
            }
            else
            {
                return "rb";
            }
        }
        else if ( mode & CREATE && mode & WRITE )
        {
            return "wb";
        }
        else if ( mode & APPEND && mode & WRITE )
        {
            return "ab";
        }

        MGE_ERROR( false, "Invalid file open mode %u", mode );

        return "";
    }

    FileHandle Open( const char8* filePath, uint32 mode )
    {
        const char8* cMode{ GetOpenMode( mode ) };

        FileHandle fileHandle{ fopen( filePath, cMode ) };

        MGE_WARNING( fileHandle, "Can't open file %s", filePath );

        return fileHandle;
    }

    void Close( FileHandle& fileHandle )
    {
        if ( fileHandle )
        {
            fclose( fileHandle );
            fileHandle = nullptr;
        }
    }

    bool Seek( FileHandle fileHandle, SeekType seek, word_t offset /* = 0 */ )
    {
        if ( seek == SEEK_FROM_CURRENT && offset == 0 )
            return true;

        int  origin{ SEEK_CUR };
        long distanceToMove{ 0 };

        switch ( seek )
        {
            case SEEK_FROM_START:
                origin         = SEEK_SET;
                distanceToMove = static_cast<long>( offset );
                break;
            case SEEK_FROM_CURRENT:
                origin         = SEEK_CUR;
                distanceToMove = static_cast<long>( offset );
                break;
            case SEEK_FROM_END:
                origin         = SEEK_END;
                distanceToMove = -static_cast<long>( offset );
                break;
        }

        return fseek( fileHandle, distanceToMove, origin ) == 0;
    }

    word_t Tell( FileHandle fileHandle )
    {
        return static_cast<word_t>( ftell( fileHandle ) );
    }

    word_t Size( FileHandle fileHandle )
    {
        word_t tell{ 0 };

        Seek( fileHandle, SEEK_FROM_END );
        tell = Tell( fileHandle );
        Seek( fileHandle, SEEK_FROM_START );

        return tell;
    }

    bool Read( FileHandle fileHandle, void* buffer, word_t length )
    {
        if ( length == 0 )
            return true;

        word_t bytesRead{ 0 };

#    if BUILD_TARGET >= BUILD_TARGET_DEBUG

        bytesRead = static_cast<word_t>( fread( buffer, 1, static_cast<size_t>( length ), fileHandle ) );

        if ( bytesRead != length )
        {
            MGE_ASSERT( false, "Read %u of %u bytes", bytesRead, length );
            return false;
        }

#    else

        bytesRead = static_cast<word_t>( fread( buffer, static_cast<size_t>( length ), 1, fileHandle ) );

        if ( bytesRead != 1 )
            return false;

#    endif

        return true;
    }

    bool Write( FileHandle fileHandle, const void* buffer, word_t length )
    {
        if ( length == 0 )
            return true;

        word_t bytesWritten{ 0 };

#    if BUILD_TARGET >= BUILD_TARGET_DEBUG

        bytesWritten = static_cast<word_t>( fwrite( buffer, 1, static_cast<size_t>( length ), fileHandle ) );

        if ( bytesWritten != length )
        {
            MGE_ASSERT( false, "Written %u of %u bytes", bytesWritten, length );
            return false;
        }

#    else

        bytesWritten = static_cast<word_t>( fwrite( buffer, static_cast<size_t>( length ), 1, fileHandle ) );

        if ( bytesWritten != 1 )
            return false;

#    endif

        return true;
    }

};    // namespace FileIO

#endif
