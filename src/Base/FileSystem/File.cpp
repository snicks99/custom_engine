#include "Common/BaseIO.h"
#include "FileSystem/File.h"
#include "FileSystem/FileIO.h"
#include "Debug/DBLAssert.h"

File::File()
    : mFilePath{}
    , mFileHandle{ nullptr }
    , mOpenMode{}
    , mSize{ 0 }
{
    mFilePath.reserve( MAX_DIR_PATH );
}

File::~File()
{
    Close();
}

bool8 File::Open( const char8* filePath, uint32 mode, Disposition disposition )
{
    FileHandle hFl{ FileIO::Open( filePath, mode, disposition ) };

    if ( hFl == nullptr )
    {
        DBL_ERROR( false, "Couldn't open file %s (%u - %u)", filePath, mode, disposition );
        return false;
    }

    Close();

    mFilePath = filePath;

    mFileHandle = hFl;

    mOpenMode = mode;

    mSize = FileIO::Size( hFl );

    return true;
}

void File::Close()
{
    mFilePath.clear();

    FileIO::Close( mFileHandle );

    mOpenMode = 0;

    mSize = 0;
}

bool File::Seek( uint32 method, int64 offset /*= 0*/ )
{
    DBL_ASSERT( mFileHandle );

    return FileIO::Seek( mFileHandle, method, offset );
}

word_t File::Tell() const
{
    DBL_ASSERT( mFileHandle );

    return FileIO::Tell( mFileHandle );
}

word_t File::Read( void* buffer, word_t length )
{
    DBL_ASSERT( mOpenMode & IO_OPEN_READ, "File %s not opened with READ flag", mFilePath.c_str() );
    DBL_ASSERT( mFileHandle );

    return FileIO::Read( mFileHandle, buffer, length );
}

word_t File::Write( const void* buffer, word_t length )
{
    DBL_ASSERT( mOpenMode & IO_OPEN_WRITE, "File %s not opened with WRITE flag", mFilePath.c_str() );
    DBL_ASSERT( mFileHandle );

    return FileIO::Write( mFileHandle, buffer, length );
}
