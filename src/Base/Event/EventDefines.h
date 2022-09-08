#ifndef EVENT_DEFINES_H
#define EVENT_DEFINES_H

#include "Common/Types.h"
#include "Hash/String/HashString.h"

using EventID = HashID;

consteval EventID HashEventID( const char8* str )
{
    return HashStringEval( str );
}

enum EventPriority : uint32
{
    EVENT_PRIORITY_LOWEST  = 0x00,
    EVENT_PRIORITY_LOW     = 0xFF,
    EVENT_PRIORITY_NORMAL  = 0xFFFF,
    EVENT_PRIORITY_HIGH    = 0xFFFFFF,
    EVENT_PRIORITY_HIGHEST = 0xFFFFFFFF
};

#endif
