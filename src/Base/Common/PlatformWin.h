#ifndef PLATFORM_WINDOWS_H
#define PLATFORM_WINDOWS_H

/****************************************************************************
 Includes
 */

#include "Common/Types.h"

/****************************************************************************
 Separator
 */

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

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
#        define DBL_DEBUG_BREAK() __debugbreak()
#    else
#        define DBL_DEBUG_BREAK()
#    endif

#    define MAX_DIR_PATH MAX_PATH

#endif

#endif
