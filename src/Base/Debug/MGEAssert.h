#ifndef MGE_ASSERT_H
#define MGE_ASSERT_H

#include "Common/Platform.h"

#define MGE_CRASH( cond, ... ) \
    {                          \
        if ( !( cond ) )       \
        {                      \
            MGE_DEBUG_BREAK(); \
        }                      \
    }

#define MGE_ASSERT( cond, ... ) \
    {                           \
        if ( !( cond ) )        \
        {                       \
            MGE_DEBUG_BREAK();  \
        }                       \
    }

#define MGE_ASSERT_NO_LOG( cond ) \
    {                             \
        if ( !( cond ) )          \
        {                         \
            MGE_DEBUG_BREAK();    \
        }                         \
    }

#define MGE_ERROR( cond, ... ) \
    {                          \
        if ( !( cond ) )       \
        {                      \
            MGE_DEBUG_BREAK(); \
        }                      \
    }

#define MGE_WARNING( cond, ... ) \
    {                            \
        if ( !( cond ) )         \
        {                        \
        }                        \
    }

#define MGE_LOG( ... ) \
    {                  \
    }

#define MGE_RW_LOG( ... ) \
    {                     \
    }

#define MGE_LOG_MESSAGE( ... ) \
    {                          \
    }

#define MGE_TRACE( ... ) \
    {                    \
    }

#define MGE_DEBUG( ... ) \
    {                    \
    }

#endif
