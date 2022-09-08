#ifndef OS_H
#define OS_H

#include "Common/Platform.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

#    include <VersionHelpers.h>

extern bool8 IsWindows11OrGreater();

#endif

class OS
{
  public:
    static void Initialize();
    static void Finalize();
};

#endif
