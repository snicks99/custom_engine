#ifndef STREAM_H
#define STREAM_H

#include "Common/Defines.h"
#include "Containers/BasicString.h"
#include "Containers/Array.h"

class Stream
{
  public:
    virtual ~Stream() = default;

    /** Write */
    template<typename T>
    Stream& operator<<( const T& val )
    {
        append( &val, sizeof( T ) );
        return *this;
    }

    Stream& operator<<( const bool8& val )
    {
        append_value<uint8>( val ? 1 : 0 );
        return *this;
    }

    template<typename T, std::size_t N>
    Stream& operator<<( Array<T, N> arr )
    {
        append( arr.data(), arr.size() );
        return *this;
    }

    Stream& operator<<( const String& str )
    {
        const word_t len{ static_cast<word_t>( str.size() ) };
        if ( len > 0 )
        {
            append( str.c_str(), len );
        }
        append_value<char8>( '\0' );
        return *this;
    }

    Stream& operator<<( const char8* str )
    {
        return operator<<( String{ str ? str : EMPTY_STRING } );
    }

    /** Read */
    template<typename T>
    Stream& operator>>( T& val )
    {
        read( &val, sizeof( T ) );
        return *this;
    }

    Stream& operator>>( bool8& val )
    {
        val = read_value<uint8>() > 0 ? true : false;
        return *this;
    }

    template<typename T, std::size_t N>
    Stream& operator>>( Array<T, N> arr )
    {
        read( arr.data(), arr.size() );
        return *this;
    }

    Stream& operator>>( String& str )
    {
        char8 c{ '\0' };
        while ( read( &c, sizeof( c ) ) == sizeof( c ) && c != '\0' )
        {
            str += c;
        }
        return *this;
    }

    /** maybe it's worthy to create LoadFromFile & SaveToFile functions - niccco */

    virtual word_t append( const void* src, word_t cnt ) = 0;

    template<typename T>
    void append_value( const T& val )
    {
        append( &val, sizeof( T ) );
    }

    virtual word_t read( void* src, word_t cnt ) = 0;

    template<typename T>
    const T read_value()
    {
        T val{};

        read( &val, sizeof( T ) );

        return val;
    }

    void read_string( String& str, uint32 len )
    {
        char8 c{ '\0' };

        str.clear();
        for ( uint32 i{ 0 }; i < len; ++i )
        {
            read( &c, sizeof( c ) );
            str += c;
        }
    }

    virtual void read_skip( word_t skip ) = 0;

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    virtual word_t size() const noexcept { return mSize; }

    virtual word_t rpos() const noexcept { return mRPos; }
    virtual word_t wpos() const noexcept { return mWPos; }

    virtual void*       data() noexcept       = 0;
    virtual const void* data() const noexcept = 0;

    virtual void* rdata() noexcept { return &( ( (uint8*)data() )[rpos()] ); }
    virtual void* wdata() noexcept { return &( ( (uint8*)data() )[wpos()] ); }

    virtual void resize( word_t ) {}

    virtual void clear() { mSize = mRPos = mWPos = 0; }

    virtual bool8 empty() const noexcept { return true; }

    virtual bool8 eof() const { return true; }

  protected:
    Stream()
        : mSize{ 0 }
        , mRPos{ 0 }
        , mWPos{ 0 }
    {
    }

    /** Copy */
    Stream( const Stream& r ) = default;

    Stream& operator=( const Stream& r )
    {
        if ( this != &r )
        {
            mSize = r.mSize;
            mRPos = r.mRPos;
            mWPos = r.mWPos;
        }

        return *this;
    }

    /** Move */
    Stream( Stream&& r ) noexcept
        : mSize{ r.mSize }
        , mRPos{ r.mRPos }
        , mWPos{ r.mWPos }
    {
        r.mSize = 0;
        r.mRPos = 0;
        r.mWPos = 0;
    }

    Stream& operator=( Stream&& r )
    {
        if ( this != &r )
        {
            mSize = r.mSize;
            mRPos = r.mRPos;
            mWPos = r.mWPos;

            r.mSize = 0;
            r.mRPos = 0;
            r.mWPos = 0;
        }

        return *this;
    }

    word_t mSize;
    word_t mRPos;
    word_t mWPos;
};

#endif
