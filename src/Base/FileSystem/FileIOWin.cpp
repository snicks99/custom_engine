#include "Common/BaseIO.h"
#include "FileSystem/FileIO.h"
#include "Debug/PrintErr.h"

#if ENABLE_STL_FILE_SYSTEM == 0 && MGE_PLATFORM == MGE_PLATFORM_WINDOWS

namespace FileIO
{

    constexpr void GetOpenMode( uint32 mode, Disposition disposition, DWORD& desiredAccess, DWORD& creationDisposition )
    {
        if ( mode & IO_OPEN_READ )
        {
            desiredAccess       = mode & IO_OPEN_WRITE ? GENERIC_READ | GENERIC_WRITE : GENERIC_READ;
            creationDisposition = OPEN_EXISTING;
        }
        else if ( mode & IO_OPEN_WRITE )
        {
            switch ( disposition )
            {
                case Disposition::CREATE:
                    desiredAccess       = GENERIC_WRITE;
                    creationDisposition = CREATE_ALWAYS;
                    break;
                case Disposition::APPEND:
                    desiredAccess       = GENERIC_WRITE;
                    creationDisposition = OPEN_ALWAYS;
                    break;
                default:
                    desiredAccess       = GENERIC_WRITE;
                    creationDisposition = OPEN_EXISTING;
                    break;
            }
        }

        PRINT_ERR( desiredAccess != 0 && creationDisposition != 0, "Invalid file open mode %u", mode );
    }

    FileHandle Open( const char8* filePath, uint32 mode, Disposition disposition )
    {
        FileHandle hFl{ nullptr };

        DWORD desiredAccess{};
        DWORD creationDisposition{};

        GetOpenMode( mode, disposition, desiredAccess, creationDisposition );

        const DWORD                 shareMode{ FILE_SHARE_READ };
        const LPSECURITY_ATTRIBUTES securityAttributes{ nullptr };
        const DWORD                 flagsAndAttributes{ FILE_ATTRIBUTE_NORMAL };
        const HANDLE                templateFile{ nullptr };

        const HANDLE h{ CreateFile( filePath, desiredAccess, shareMode, securityAttributes, creationDisposition, flagsAndAttributes, templateFile ) };

        if ( h == nullptr || h == INVALID_HANDLE_VALUE )
        {
            PRINT_ERR( false, "Couldn't open file %s (%u)", filePath, GetLastError() );
            return nullptr;
        }

        hFl = h;

        /** since we are going to append, go to EOF - niccco */
        if ( disposition == Disposition::APPEND )
        {
            Seek( hFl, IO_SEEK_END );
        }

        return hFl;
    }

    void Close( FileHandle& hFl )
    {
        if ( hFl )
        {
            PRINT_ERR( CloseHandle( hFl ), "Error %u closing file", GetLastError() );
            hFl = nullptr;
        }
    }

    bool8 Seek( FileHandle hFl, uint32 method, int64 offset /* = 0 */ )
    {
        if ( method == IO_SEEK_CUR && offset == 0 )
            return true;

        LARGE_INTEGER        distanceToMove{};
        const PLARGE_INTEGER newFilePointer{ nullptr };
        DWORD                moveMethod{};

        switch ( method )
        {
            case IO_SEEK_BEG:
                moveMethod              = FILE_BEGIN;
                distanceToMove.QuadPart = static_cast<LONGLONG>( offset );
                break;
            case IO_SEEK_CUR:
                moveMethod              = FILE_CURRENT;
                distanceToMove.QuadPart = static_cast<LONGLONG>( offset );
                break;
            case IO_SEEK_END:
                moveMethod              = FILE_END;
                distanceToMove.QuadPart = static_cast<LONGLONG>( offset );
                break;
            default:
            {
                PRINT_ERR( false, "Invalid seek method %u", method );
                return false;
            }
            break;
        }

        return SetFilePointerEx( hFl, distanceToMove, newFilePointer, moveMethod ) != 0;
    }

    word_t Tell( FileHandle hFl )
    {
        LARGE_INTEGER distanceToMove{};
        LARGE_INTEGER newFilePointer{};
        const DWORD   moveMethod{ FILE_CURRENT };

        PRINT_ERR( SetFilePointerEx( hFl, distanceToMove, &newFilePointer, moveMethod ) );

        return static_cast<word_t>( newFilePointer.QuadPart );
    }

    word_t Size( FileHandle hFl )
    {
        LARGE_INTEGER fileSize{};

        PRINT_ERR( GetFileSizeEx( hFl, &fileSize ) );

        return static_cast<word_t>( fileSize.QuadPart );
    }

    word_t Read( FileHandle hFl, void* buffer, word_t length )
    {
        if ( length == 0 )
            return 0;

        PRINT_ERR( length < 0xFFFFFFFF, "lenght out of boundary" );

        DWORD numberOfBytesToRead{ static_cast<DWORD>( length ) };
        DWORD numberOfBytesRead{ 0 };

        PRINT_ERR( ReadFile( hFl, buffer, numberOfBytesToRead, &numberOfBytesRead, nullptr ), "Error %u can't read %u bytes", GetLastError(), numberOfBytesToRead );

        return numberOfBytesRead;
    }

    word_t Write( FileHandle hFl, const void* buffer, word_t length )
    {
        if ( length == 0 )
            return 0;

        PRINT_ERR( length < 0xFFFFFFFF, "lenght out of boundary" );

        DWORD numberOfBytesToWrite{ static_cast<DWORD>( length ) };
        DWORD numberOfBytesWritten{ 0 };

        PRINT_ERR( WriteFile( hFl, buffer, numberOfBytesToWrite, &numberOfBytesWritten, nullptr ), "Error %u can't write %u bytes", GetLastError(), numberOfBytesToWrite );

        return numberOfBytesWritten;
    }

    bool8 Exists( const char8* filePath )
    {
        const DWORD fileAttributes{ GetFileAttributes( filePath ) };

        return ( fileAttributes != INVALID_FILE_ATTRIBUTES ) &&
               ( fileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0;
    }

};    // namespace FileIO

#endif
