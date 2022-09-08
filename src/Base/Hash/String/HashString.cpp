#include "Hash/String/HashString.h"
#include "Debug/DBLAssert.h"

HashID HashString( const char8* str )
{
    DBL_ASSERT( str && str[0] != '\0', "Can't hash an invalid string" );

    return CRC32::HashString( str );
}
