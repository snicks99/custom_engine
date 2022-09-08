#include "Memory/MMU.h"

#if 1

#    include "Memory/Allocator/DLMalloc.h"

void* alloc( word_t bytes, word_t align )
{
    return dlmemalign( static_cast<size_t>( align ), static_cast<size_t>( bytes ) );
}

void dealloc( void* mem )
{
    dlfree( mem );
}

void* ralloc( void* oldmem, word_t bytes )
{
    return dlrealloc( oldmem, static_cast<size_t>( bytes ) );
}

void* zalloc( word_t n_elements, word_t elem_size )
{
    return dlcalloc( static_cast<size_t>( n_elements ), static_cast<size_t>( elem_size ) );
}

#else

void* alloc( word_t bytes, word_t align )
{
    return malloc( bytes );
}

void dealloc( void* mem )
{
    free( mem );
}

void* ralloc( void* oldmem, word_t bytes )
{
    return realloc( oldmem, bytes );
}

void* zalloc( word_t n_elements, word_t elem_size )
{
    return calloc( n_elements, elem_size );
}

#endif

/* ===== Global ===== */
#ifdef OVERRIDE_GLOBAL_NEW_DELETE

void* operator new( std::size_t count )
{
    return alloc( static_cast<word_t>( count ) );
}

void* operator new[]( std::size_t count )
{
    return alloc( static_cast<word_t>( count ) );
}

void* operator new( std::size_t count, std::align_val_t al )
{
    return alloc( static_cast<word_t>( count ), static_cast<word_t>( al ) );
}

void* operator new[]( std::size_t count, std::align_val_t al )
{
    return alloc( static_cast<word_t>( count ), static_cast<word_t>( al ) );
}

void operator delete( void* ptr ) noexcept
{
    dealloc( ptr );
}

void operator delete[]( void* ptr ) noexcept
{
    dealloc( ptr );
}

void operator delete( void* ptr, std::align_val_t al ) noexcept
{
    dealloc( ptr );
}

void operator delete[]( void* ptr, std::align_val_t al ) noexcept
{
    dealloc( ptr );
}

#endif
