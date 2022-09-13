#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/** only for macro define we use double '/' */

/** this should be per project */

/****************************************************************************
 Includes
 */

#include "Common/Platform.h"

/****************************************************************************
 Separator
 */

#define OVERRIDE_GLOBAL_NEW_DELETE

// #define ENABLE_MEMORY_TRACK

// #define ENABLE_DISCORD
// #define ENABLE_ANALYTICS

/****************************************************************************
 Separator
 */

#define ENABLE_DLMALLOC 1

/** enable STD functions */
#define ENABLE_STL_DEF_DEL   0
#define ENABLE_STL_ALLOCATOR 1
#if MGE_PLATFORM == MGE_PLATFORM_WINDOWS
#    define ENABLE_STL_FILE_SYSTEM 0
#elif MGE_PLATFORM == MGE_PLATFORM_UNIX
#    define ENABLE_STL_FILE_SYSTEM 1
#else
#    define ENABLE_STL_FILE_SYSTEM 0
#endif
#define ENABLE_STL_SHARED_PTR     0
#define ENABLE_STL_BASIC_STRING   1
#define ENABLE_STL_ARRAY          0
#define ENABLE_STL_VECTOR         0
#define ENABLE_STL_LIST           0
#define ENABLE_STL_DEQUEUE        0
#define ENABLE_STL_QUEUE          1
#define ENABLE_STL_PRIORITY_QUEUE 0
#define ENABLE_STL_SET            0
#define ENABLE_STL_UNORDERED_SET  0
#define ENABLE_STL_MAP            0
#define ENABLE_STL_UNORDERED_MAP  0

/** enable BOOST functions */
#define ENABLE_BOOST_DEF_DEL        1
#define ENABLE_BOOST_ALLOCATOR      0 /** boost allocator use DLMalloc which we already use - niccco */
#define ENABLE_BOOST_SHARED_PTR     1
#define ENABLE_BOOST_BASIC_STRING   1
#define ENABLE_BOOST_ARRAY          1
#define ENABLE_BOOST_VECTOR         1
#define ENABLE_BOOST_LIST           1
#define ENABLE_BOOST_DEQUEUE        1
#define ENABLE_BOOST_QUEUE          1
#define ENABLE_BOOST_PRIORITY_QUEUE 1
#define ENABLE_BOOST_SET            1
#define ENABLE_BOOST_UNORDERED_SET  1
#define ENABLE_BOOST_MAP            1
#define ENABLE_BOOST_UNORDERED_MAP  1

#endif
