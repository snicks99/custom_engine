#ifndef BYTE_STREAM_H
#define BYTE_STREAM_H

#include "Containers/Vector.h"
#include "Stream/Stream.h"

CONSTEXPR_INLINE word_t BYTE_BUFFER_SIZE{ 4 * MEMORY_KIBIBYTE };

class MessageBuffer;

class ByteStream : public Stream
{
  public:
    ByteStream( word_t reserve = BYTE_BUFFER_SIZE )
        : Stream{}
        , mBuffer{}
    {
        mBuffer.reserve( BYTE_BUFFER_SIZE );
    }

    /** Copy */
    ByteStream( const ByteStream& r ) = default;

    ByteStream& operator=( const ByteStream& r )
    {
        Stream::operator=( r );

        if ( this != &r )
        {
            mBuffer = r.mBuffer;
        }

        return *this;
    }

    /** Move */
    ByteStream( ByteStream&& r ) noexcept
        : Stream{ std::move( r ) }
        , mBuffer{ std::move( r.mBuffer ) }
    {
    }

    ByteStream( MessageBuffer&& r ) noexcept = delete;

    ByteStream& operator=( ByteStream&& r ) noexcept
    {
        Stream::operator=( std::move( r ) );

        if ( this != &r )
        {
            mBuffer = std::move( r.mBuffer );
        }

        return *this;
    }

    virtual ~ByteStream() = default;

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    word_t append( const void* src, word_t cnt ) override;
    word_t read( void* dst, word_t cnt ) override;

    void read_skip( word_t skip ) override;

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    word_t size() const noexcept override { return mBuffer.size(); }

    void*       data() noexcept override { return mBuffer.data(); }
    const void* data() const noexcept override { return mBuffer.data(); }

    void resize( word_t size ) override;

    void clear() override
    {
        Stream::clear();

        mBuffer.clear();
    }

    bool8 empty() const noexcept override { return mBuffer.empty(); }

    bool8 eof() const override;

  protected:
    Vector<uint8> mBuffer;
};

#endif
