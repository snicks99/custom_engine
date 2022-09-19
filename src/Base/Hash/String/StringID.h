#ifndef STRING_ID_H
#define STRING_ID_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"
#include "Hash/String/HashString.h"

#include <xhash>
#include <boost/container_hash/hash.hpp>

class StringID
{
  public:
    constexpr StringID( MGE_SID sid = INVALID_MGE_SID ) noexcept
        : mSID{ sid }
    {
    }

    constexpr StringID( const char8* str ) noexcept
        : mSID{ HashStringExpr( str ) }
    {
    }

    constexpr StringID( const String& str ) noexcept
        : mSID{ HashStringExpr( str.c_str() ) }
    {
    }

    /** Copy */
    constexpr StringID( const StringID& r ) noexcept
        : mSID{ r.GetSID() }
    {
    }

    constexpr StringID& operator=( const StringID& r ) noexcept
    {
        SetSID( r.GetSID() );
        return *this;
    }

    /** Move */
    constexpr StringID( StringID&& r ) noexcept
        : mSID{ r.GetSID() }
    {
        r.SetSID( INVALID_MGE_SID );
    }

    constexpr StringID& operator=( StringID&& r ) noexcept
    {
        SetSID( r.GetSID() );
        r.SetSID( INVALID_MGE_SID );
        return *this;
    }

    /** Other */
    constexpr StringID& operator=( const char8* str ) noexcept
    {
        SetSID( HashStringExpr( str ) );
        return *this;
    }

    constexpr StringID& operator=( const String& r ) noexcept
    {
        SetSID( HashStringExpr( r.c_str() ) );
        return *this;
    }

    constexpr bool8 operator==( const StringID& r ) const noexcept
    {
        return GetSID() == r.GetSID();
    }

    constexpr bool8 operator==( StringID&& r ) const noexcept
    {
        return GetSID() == r.GetSID();
    }

    constexpr void    SetSID( MGE_SID sid ) noexcept { mSID = sid; }
    constexpr MGE_SID GetSID() const noexcept { return mSID; }

    constexpr operator MGE_SID() const noexcept { return GetSID(); }

  protected:
    MGE_SID mSID;
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
