#ifndef PLATFORM_WINDOWS_H
#define PLATFORM_WINDOWS_H

/****************************************************************************
 Includes
 */

#include "Common/Types.h"

/****************************************************************************
 Separator
 */

#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS

#    include <windows.h>
#    include <float.h>

#    ifndef NOMINMAX
// undef macro min and max from windows headers
#        define NOMINMAX
#    endif

#    undef min
#    undef max

#    define FORCE_INLINE __forceinline

#    if BUILD_TARGET >= BUILD_TARGET_DEBUG
#        define MGE_DEBUG_BREAK() __debugbreak()
#    else
#        define MGE_DEBUG_BREAK()
#    endif

#    define MAX_DIR_PATH MAX_PATH

#endif

#endif
