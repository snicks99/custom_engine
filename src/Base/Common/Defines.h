#ifndef DEFINES_H
#define DEFINES_H

/****************************************************************************
 Includes
 */

#include "Common/ProjectConfig.h"
#include <memory>

/****************************************************************************
 Separator
 */

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_4
#    define M_PI_4 0.785398163397448309616
#endif

template<typename T>
inline void Clamp( T& val, const T& min, const T& max )
{
    val = std::max( min, std::max( val, max ) );
}

/****************************************************************************
 Separator
 */

#define STRINGIZE( s ) #s

/****************************************************************************
 Separator
 */

CONSTEXPR_INLINE word_t MEMORY_KIBIBYTE{ 1024 };
CONSTEXPR_INLINE word_t MEMORY_MEBIBYTE{ 1024 * MEMORY_KIBIBYTE };
CONSTEXPR_INLINE word_t MEMORY_GIBIBYTE{ 1024 * MEMORY_MEBIBYTE };

/****************************************************************************
 Separator
 */

inline uint64 MAKE_PAIR64( uint32 l, uint32 h )
{
    return ( static_cast<uint64>( h ) << 32 ) | static_cast<uint64>( l );
}

inline uint32 PAIR64_LOW( uint64 v )
{
    return static_cast<uint32>( v & UI64LIT( 0x00000000FFFFFFFF ) );
}

inline uint32 PAIR64_HIGH( uint64 v )
{
    return static_cast<uint32>( v >> 32 );
}

/****************************************************************************
 Separator
 */

struct PtrLess
{
  public:
    template<typename T>
    CONSTEXPR_INLINE bool operator()( const T& l, const T& r ) const
    {
        return std::addressof( *l ) < std::addressof( *r );
    }
};

struct PtrGreater
{
  public:
    template<typename T>
    CONSTEXPR_INLINE bool operator()( const T& l, const T& r ) const
    {
        return std::addressof( *l ) > std::addressof( *r );
    }
};

struct PairSecondLess
{
  public:
    template<typename T>
    CONSTEXPR_INLINE bool operator()( const T& l, const T& r ) const
    {
        return l.second < r.second;
    }
};

struct PairSecondGreater
{
  public:
    template<typename T>
    CONSTEXPR_INLINE bool operator()( const T& l, const T& r ) const
    {
        return l.second > r.second;
    }
};

/****************************************************************************
 Separator
 */

template<typename T>
inline void SafeDelete( T*& ptr )
{
    if ( ptr )
    {
        delete ptr;
        ptr = nullptr;
    }
}

template<typename T>
inline void SafeDeleteArray( T*& ptr )
{
    if ( ptr )
    {
        delete[] ptr;
        ptr = nullptr;
    }
}

#endif
