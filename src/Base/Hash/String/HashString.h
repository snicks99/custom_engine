#ifndef HASH_STRING_H
#define HASH_STRING_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"
#include "Hash/String/HashDJB2.h"
#include "Hash/String/HashCRC32.h"
#include "Utilities/Utils.h"

constexpr HashID HashStringExpr( const char8* str )
{
    return CRC32::HashString( str );
}

consteval HashID HashStringEval( const char8* str )
{
    return HashStringExpr( str );
}

extern HashID HashString( const char8* str );

#endif
