#ifndef STRING_ID_H
#define STRING_ID_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"
#include "Hash/String/HashString.h"

#include <xhash>
#include <boost/container_hash/hash.hpp>

/** use this consteval so we create compile-time StringID - niccco */
consteval HashID MAKE_SID( const char8* str )
{
    return HashStringEval( str );
}

class StringID
{
  public:
    constexpr StringID( HashID strId = 0xFFFFFFFF )
        : mStrId{ strId }
    {
    }

    constexpr StringID( const char8* str )
        : mStrId{ HashStringExpr( str ) }
    {
    }

    StringID( StringView str )
        : mStrId{ HashString( str.data() ) }
    {
    }

    StringID( const String& str )
        : mStrId{ HashString( str.c_str() ) }
    {
    }

    /** Copy */
    StringID( const StringID& r )
        : mStrId{ r.GetSID() }
    {
    }

    StringID& operator=( const StringID& r )
    {
        SetSID( r.GetSID() );
        return *this;
    }

    /** Move */
    StringID( StringID&& r ) noexcept
        : mStrId{ r.GetSID() }
    {
        r.SetSID( 0xFFFFFFFF );
    }

    StringID& operator=( StringID&& r ) noexcept
    {
        SetSID( r.GetSID() );
        r.SetSID( 0xFFFFFFFF );
        return *this;
    }

    /** Other */
    StringID& operator=( StringView r )
    {
        SetSID( HashString( r.data() ) );
        return *this;
    }

    StringID& operator=( const String& r )
    {
        SetSID( HashString( r.c_str() ) );
        return *this;
    }

    StringID& operator=( const char8* r )
    {
        SetSID( HashString( r ) );
        return *this;
    }

    constexpr bool operator==( const StringID& r ) const noexcept
    {
        return GetSID() == r.GetSID();
    }

    constexpr bool operator==( StringID&& r ) const noexcept
    {
        return GetSID() == r.GetSID();
    }

    constexpr void   SetSID( HashID strId ) noexcept { mStrId = strId; }
    constexpr HashID GetSID() const noexcept { return mStrId; }

    FORCE_INLINE operator HashID() const noexcept { return GetSID(); }

  protected:
    HashID mStrId;
};

template<>
struct std::hash<StringID>
{
  public:
    std::size_t operator()( const StringID& strId ) const noexcept
    {
        return static_cast<std::size_t>( strId.GetSID() );
    }
};

template<>
struct boost::hash<StringID>
{
  public:
    std::size_t operator()( const StringID& strId ) const noexcept
    {
        return static_cast<std::size_t>( strId.GetSID() );
    }
};

#endif
