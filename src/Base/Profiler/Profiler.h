#ifndef PROFILER_H
#define PROFILER_H

#include "Clock/SystemTime.h"
#include "Containers/Set.h"

#define ENABLE_PROFILER
#define ENABLE_OPTICK_PROFILER
// #define ENABLE_PROFILER_UI

// extra
#ifdef ENABLE_OPTICK_PROFILER
#    include "optick.h"
#else
#    define OPTICK_SET_MEMORY_ALLOCATOR( ALLOCATE_FUNCTION, DEALLOCATE_FUNCTION, INIT_THREAD_CALLBACK )
#    define OPTICK_SHUTDOWN()

#    define OPTICK_FRAME( FRAME_NAME, ... )

#    define OPTICK_THREAD( THREAD_NAME )
#endif

#ifdef ENABLE_PROFILER

#    ifdef ENABLE_OPTICK_PROFILER
#        define PROFILE_FN( name )                     OPTICK_CATEGORY( name, Optick::Category::None )
#        define PROFILE_OPTICK_SCOPE( name, category ) OPTICK_CATEGORY( name, category )
#    else
#        define PROFILE_FN( name ) \
            ProfileFn profiler { name }
#        define PROFILE_OPTICK_SCOPE( name, category )
#    endif

#else

#    define PROFILE_FN( name )
#    define PROFILE_OPTICK_SCOPE( name, category )

#endif

#endif
