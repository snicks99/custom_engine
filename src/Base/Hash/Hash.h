#ifndef HASH_H
#define HASH_H

#include "Common/Platform.h"

using HashID = word_t;

CONSTEXPR_INLINE HashID INVALID_HASH_ID{ std::numeric_limits<HashID>::max() };

#if 0

// Base hash type
// Any child (template specialized) structure
// should implement for specific type T:
// - hash function: operator()(T value)
// - compare function: compare(T value1, T value2)
template<typename T>
struct Hash
{
};

// specialization for all pointers
template<typename T>
struct Hash<T*>
{
    size_t operator()( T* pointer ) const
    {
        return reinterpret_cast<size_t>( pointer );
    }

    bool Compare( T* ptr1, T* ptr2 ) const
    {
        return ( ptr1 == ptr2 );
    }
};

template<>
struct Hash<int32>
{
    size_t operator()( const int32 i ) const
    {
        return i;
    }

    bool Compare( const int32 i1, const int32 i2 ) const
    {
        return ( i1 == i2 );
    }
};

template<>
struct Hash<uint32>
{
    size_t operator()( const uint32 i ) const
    {
        return i;
    }

    bool Compare( const uint32 i1, const uint32 i2 ) const
    {
        return i1 == i2;
    }
};

template<typename T>
inline void HashCombine( std::size_t& seed, const T& val )
{
    seed ^= std::hash<T>()( val ) + 0x9E3779B9 + ( seed << 6 ) + ( seed >> 2 );
}

//! Hash implementation for std::pair to allow using pairs in unordered_set or as key for unordered_map
//! Individual types used in pair must be hashable by std::hash
namespace std
{
    template<typename K, typename V>
    struct hash<std::pair<K, V>>
    {
      public:
        std::size_t operator()( const std::pair<K, V>& p ) const
        {
            std::size_t hashVal{ 0 };

            HashCombine( hashVal, p.first );
            HashCombine( hashVal, p.second );

            return hashVal;
        }
    };
}    // namespace std

#endif

#endif
