#include "Stream/ByteStream.h"
#include "Debug/DBLAssert.h"

void ByteStream::resize( word_t size )
{
    mBuffer.resize( size );

    mRPos = 0;
    mWPos = size;
}

bool8 ByteStream::eof() const
{
    return rpos() >= size();
}

word_t ByteStream::append( const void* src, word_t cnt )
{
    if ( cnt == 0 )
        return 0;

    const word_t newSize{ mWPos + cnt };

    /** allocation */
    if ( newSize > mBuffer.capacity() )
    {
        if ( newSize < 2 * MEMORY_KIBIBYTE )
        {
            mBuffer.reserve( 2 * MEMORY_KIBIBYTE );
        }
        else if ( newSize < 4 * MEMORY_KIBIBYTE )
        {
            mBuffer.reserve( 4 * MEMORY_KIBIBYTE );
        }
        else if ( newSize < 8 * MEMORY_KIBIBYTE )
        {
            mBuffer.reserve( 8 * MEMORY_KIBIBYTE );
        }
        else
        {
            mBuffer.reserve( 512 * MEMORY_KIBIBYTE );
        }
    }

    if ( newSize > size() )
    {
        mBuffer.resize( newSize );
    }

    memcpy( &mBuffer[mWPos], src, cnt );

    mWPos = newSize;

    return cnt;
}

word_t ByteStream::read( void* dst, word_t cnt )
{
    if ( cnt == 0 )
        return 0;

    if ( mRPos + cnt > size() )
    {
        DBL_ERROR( false, "ByteStream overflow" );
        return 0;
    }

    memcpy( dst, &mBuffer[mRPos], cnt );

    mRPos += cnt;

    return cnt;
}

void ByteStream::read_skip( word_t skip )
{
    if ( mRPos + skip > size() )
    {
        DBL_ERROR( false, "ByteStream overflow" );
        return;
    }

    mRPos += skip;
}
