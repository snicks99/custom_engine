#ifndef PLATFORM_UNIX_H
#define PLATFORM_UNIX_H

/****************************************************************************
 Includes
 */

#include "Common/Types.h"

/****************************************************************************
 Separator
 */

#if MGE_COMPILER == MGE_COMPILER_GNU

#    include <signal.h>
#    include <climits>

#    define FORCE_INLINE __attribute__( ( __always_inline__ ) )

#    if BUILD_TARGET >= BUILD_TARGET_DEBUG
#        ifdef SIGTRAP
#            define MGE_DEBUG_BREAK() raise( SIGTRAP )
#        else
#            define MGE_DEBUG_BREAK() raise( SIGABRT )
#        endif
#    else
#        define MGE_DEBUG_BREAK()
#    endif

#    define MAX_DIR_PATH PATH_MAX

#    define sprintf_s( buf, ... ) snprintf( ( buf ), sizeof( buf ), __VA_ARGS__ )

#endif

#endif
