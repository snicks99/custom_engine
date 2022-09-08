#ifndef MEMORY_MANAGEMENT_UNIT_H
#define MEMORY_MANAGEMENT_UNIT_H

#include "Common/Defines.h"

void* alloc( word_t bytes, word_t align = sizeof( word_t ) );
void  dealloc( void* mem );
void* ralloc( void* oldmem, word_t bytes );
void* zalloc( word_t n_elements, word_t elem_size );

#ifdef OVERRIDE_GLOBAL_NEW_DELETE

#    include <cstdio>
#    include <new>

void* operator new( std::size_t count );
void* operator new[]( std::size_t count );
void* operator new( std::size_t count, std::align_val_t al );
void* operator new[]( std::size_t count, std::align_val_t al );

void operator delete( void* ptr ) noexcept;
void operator delete[]( void* ptr ) noexcept;
void operator delete( void* ptr, std::align_val_t al ) noexcept;
void operator delete[]( void* ptr, std::align_val_t al ) noexcept;

#endif

#if ENABLE_STL_DEF_DEL

#    include <memory>

template<typename T>
using DefDel = std::default_delete<T>;

template<typename T>
using DefArrDel = std::default_delete<T[]>;

#elif ENABLE_BOOST_DEF_DEL

#    include <boost/move/default_delete.hpp>

template<typename T>
using DefDel = boost::movelib::default_delete<T>;

template<typename T>
using DefArrDel = boost::movelib::default_delete<T[]>;

#endif

#endif
