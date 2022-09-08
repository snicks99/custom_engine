#ifndef HASH_DJB2_H
#define HASH_DJB2_H

#include "Utilities/Utils.h"

namespace DJB2
{

    constexpr HashID Hash( const char8* str )
    {
        HashID hash{ 5381 };

        for ( ; *str; ++str )
            hash = ( ( hash << 5 ) + hash ) + *str;

        return hash;
    }

    constexpr HashID HashString( const char8* str )
    {
        HashID hash{ 5381 };

        for ( ; *str; ++str )
            hash = ( ( hash << 5 ) + hash ) + cToLower( *str );

        return hash;
    }

};    // namespace DJB2

#endif
