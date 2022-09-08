#include "Common/BaseIO.h"
#include "Stream/FileStream.h"
#include "Stream/StreamDefines.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "FileSystem/Pack/RscPakDefines.h"
#include "FileSystem/Pak/PAKFile.h"
#include "Debug/DBLAssert.h"

/************************************************************************/
/*                                  Buffer                              */
/************************************************************************/
FileStream::FileStream()
    : Stream{}
    , mFile{ nullptr }
    , mBuffer{}
{
}

FileStream::~FileStream()
{
    if ( IsOpen() )
    {
        if ( mFile->GetOpenMode() & IO_OPEN_WRITE )
        {
            WriteBufferChunk();
        }
    }
}

bool8 FileStream::Open( const char8* filePath, uint32 mode, Disposition disposition /*= Disposition::NONE*/ )
{
    bool8 isOpen{ false };

    mFile = new File{};

    isOpen = mFile->Open( filePath, mode, disposition );
    if ( isOpen )
    {
        mBuffer.resize( FILE_STREAM_BUFFER_SIZE );

        if ( mode & IO_OPEN_READ )
        {
            ReadBufferChunk();
        }
        else if ( mode & IO_OPEN_WRITE )
        {
            WriteBufferChunk();
        }
    }

    return isOpen;
}

bool8 FileStream::OpenPak( uint32 pak, const char8* filePath )
{
    bool8 isOpen{ false };

    mFile = new PAKFile{};

    isOpen = ( (PAKFile*)mFile.get() )->Open( pak, filePath );
    if ( isOpen )
    {
        mBuffer.resize( FILE_STREAM_BUFFER_SIZE );

        ReadBufferChunk();
    }

    return isOpen;
}

bool8 FileStream::IsOpen() const
{
    return mFile && mFile->IsOpen();
}

bool8 FileStream::eof() const
{
    return IsOpen() == false || mFile->Tell() >= mFile->Size();
}

word_t FileStream::append( const void* src, word_t cnt )
{
    word_t ret{ 0 };

    word_t remnSize{ mSize - mWPos };
    word_t buffSize{ cnt > remnSize ? remnSize : cnt };

    while ( buffSize > 0 && mWPos < mSize )
    {
        memcpy( &mBuffer[mWPos], src, buffSize );

        mWPos += buffSize;

        ret += buffSize;
        cnt -= buffSize;

        remnSize -= buffSize;
        if ( remnSize == 0 )
        {
            src = static_cast<const uint8*>( src ) + buffSize;

            WriteBufferChunk();
            remnSize = mSize - mWPos;
        }
        buffSize = cnt > remnSize ? remnSize : cnt;
    }

    return ret;
}

word_t FileStream::read( void* src, word_t cnt )
{
    word_t ret{ 0 };

    word_t remnSize{ mSize - mRPos };
    word_t readSize{ cnt > remnSize ? remnSize : cnt };

    while ( readSize > 0 && mRPos < mSize )
    {
        memcpy( src, &mBuffer[mRPos], readSize );

        mRPos += readSize;

        ret += readSize;
        cnt -= readSize;

        remnSize -= readSize;
        if ( remnSize == 0 )
        {
            src = static_cast<uint8*>( src ) + readSize;

            ReadBufferChunk();
            remnSize = mSize - mRPos;
        }
        readSize = cnt > remnSize ? remnSize : cnt;
    }

    return ret;
}

void FileStream::read_skip( word_t skip )
{
    word_t remnSize{ mSize - mRPos };
    word_t readSize{ skip > remnSize ? remnSize : skip };

    while ( readSize > 0 && mRPos < mSize )
    {
        mRPos += readSize;

        skip -= readSize;

        remnSize -= readSize;
        if ( remnSize == 0 )
        {
            ReadBufferChunk();
            remnSize = mSize - mRPos;
        }
        readSize = skip > remnSize ? remnSize : skip;
    }
}

void FileStream::ReadBufferChunk()
{
    const word_t size{ mFile->Size() };
    const word_t tell{ mFile->Tell() };

    const word_t remnSize{ tell + FILE_STREAM_BUFFER_SIZE > size ? size - tell : FILE_STREAM_BUFFER_SIZE };

    mSize = mFile->Read( mBuffer.data(), remnSize );
    mRPos = 0;
}

void FileStream::WriteBufferChunk()
{
    const bool8 success{ mFile->Write( mBuffer.data(), mWPos ) == mWPos };

    if ( success == false )
        return;

    /** if we reset mPos, maybe cleaning the data isn't really necessary - niccco */
    memset( mBuffer.data(), 0x00, mBuffer.size() );

    mSize = mBuffer.size();
    mWPos = 0;
}
