#ifndef COMPILER_DEFS_H
#define COMPILER_DEFS_H

#include <stdio.h>

/****************************************************************************
 Separator
 */

#define MGE_PLATFORM_WINDOWS 0
#define MGE_PLATFORM_UNIX    1
#define MGE_PLATFORM_APPLE   2
#define MGE_PLATFORM_INTEL   3

/** first check _WIN64 then _WIN32 */
#if defined( _WIN64 )
#    define MGE_PLATFORM MGE_PLATFORM_WINDOWS
#elif defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#    define MGE_PLATFORM MGE_PLATFORM_WINDOWS
#else
#    define MGE_PLATFORM MGE_PLATFORM_UNIX
#endif

#define MGE_COMPILER_MICROSOFT 0
#define MGE_COMPILER_GNU       1
#define MGE_COMPILER_BORLAND   2
#define MGE_COMPILER_INTEL     3

#ifdef _MSC_VER
#    define MGE_COMPILER MGE_COMPILER_MICROSOFT
#elif defined( __BORLANDC__ )
#    define MGE_COMPILER MGE_COMPILER_BORLAND
#elif defined( __INTEL_COMPILER )
#    define MGE_COMPILER MGE_COMPILER_INTEL
#elif defined( __GNUC__ )
#    define MGE_COMPILER MGE_COMPILER_GNU
#    define GCC_VERSION  ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
#else
#    error "FATAL ERROR: Unknown compiler."
#endif

#define BUILD_TARGET_FINAL   0
#define BUILD_TARGET_RELEASE 1
#define BUILD_TARGET_DEBUG   2

#ifndef BUILD_TARGET
#    define BUILD_TARGET BUILD_TARGET_RELEASE
#endif

#endif
