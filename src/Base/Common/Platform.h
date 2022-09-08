#ifndef PLATFORM_H
#define PLATFORM_H

/****************************************************************************
 Includes
 */

#include "Common/Types.h"
#include "Common/PlatformWin.h"
#include "Common/PlatformUnix.h"

#ifdef _countof
#    define ARRAY_SIZE( arr ) ( _countof( arr ) )
#else
#    define ARRAY_SIZE( arr ) ( sizeof( arr ) / sizeof( arr[0] ) )
#endif

#if BUILD_TARGET <= BUILD_TARGET_RELEASE
#    define RELEASE_INLINE inline
#else
#    define RELEASE_INLINE
#endif

#define CONSTEXPR_INLINE  constexpr inline
#define CONSTEXPR_VIRTUAL constexpr virtual

#if DBL_COMPILER == DBL_COMPILER_GNU
#    define ATTR_PRINTF( F, V ) __attribute__( ( __format__( __printf__, F, V ) ) )
#else
#    define ATTR_PRINTF( F, V )
#endif

#endif
