#ifndef HASH_STRING_H
#define HASH_STRING_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"
#include "Hash/Hash.h"
#include "Hash/String/HashCRC32.h"
#include "Utilities/Utils.h"

constexpr MGE_SID HashStringExpr( const char8* str )
{
    return static_cast<MGE_SID>( CRC32::HashString( str ) );
}

extern MGE_SID HashString( const char8* str );

#endif
