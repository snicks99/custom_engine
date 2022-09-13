#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "Memory/Allocators.h"
#include "Debug/MGEAssert.h"

class MemoryPool
{
  public:
    struct Chunk
    {
      public:
        Chunk()
            : mNext{ nullptr }
        {
        }

        Chunk* mNext;
    };

  public:
    MemoryPool( word_t chunkSize, word_t numChunk, word_t align = sizeof( word_t ), const char8* name = nullptr )
        : mName{ name ? name : "Base" }
        , mAlloc{}
        , mMem{ nullptr }
        , mFreeList{ nullptr }
        , mChunkSize{ chunkSize }
        , mNumChunk{ numChunk }
        , mAlign{ align }
        , mMemChunk{ ( sizeof( Chunk ) + mChunkSize ) * mNumChunk }
    {
        mMem = mFreeList = AllocBlock();
    }

    ~MemoryPool()
    {
        mAlloc.deallocate( static_cast<uint8*>( mMem ), static_cast<std::size_t>( mMemChunk ) );
    }

    void* allocate( std::size_t bytes )
    {
        MGE_ASSERT( static_cast<word_t>( bytes ) <= mChunkSize, "MemoryPool %s is trying to allocate a larger chunk %u", get_name(), bytes );

        if ( mFreeList == nullptr )
        {
            MGE_ERROR( false, "MemoryPool %s is empty", get_name() );
            return nullptr;
        }

        /** we want to return the data - niccco */
        void* freeChunk{ reinterpret_cast<char*>( mFreeList ) + sizeof( Chunk ) };

        mFreeList = mFreeList->mNext;

        return freeChunk;
    }

    void deallocate( void* p, std::size_t )
    {
        if ( p == nullptr )
        {
            MGE_ASSERT( false, "MemoryPool %s trying to free a null pointer", get_name() );
            return;
        }

        Chunk* chunk{ reinterpret_cast<Chunk*>( reinterpret_cast<char*>( p ) - sizeof( Chunk ) ) };

        chunk->mNext = mFreeList;
        mFreeList    = chunk;
    }

  protected:
    const char8* get_name() const
    {
        return mName;
    }

    Chunk* AllocBlock()
    {
        Chunk* blockBegin{ reinterpret_cast<Chunk*>( mAlloc.allocate( static_cast<std::size_t>( mMemChunk ) ) ) };

        MGE_ASSERT( blockBegin, "MemoryPool %s couldn't allocate %u ( %u * %u ) bytes", get_name(), mMemChunk, mChunkSize, mNumChunk );

        Chunk* chunk{ blockBegin };

        for ( size_t i{ 0 }, numChunk{ mNumChunk - 1 }; i < numChunk; ++i )
        {
            chunk->mNext = reinterpret_cast<Chunk*>( reinterpret_cast<char*>( chunk ) + ( sizeof( Chunk ) + mChunkSize ) );
            chunk        = chunk->mNext;
        }

        chunk->mNext = nullptr;

        return blockBegin;
    }

    const char8* mName;

    HeapAllocator<uint8> mAlloc;
    void*                mMem;
    Chunk*               mFreeList;
    word_t               mChunkSize;
    word_t               mNumChunk;
    word_t               mAlign;
    word_t               mMemChunk;
};

#endif
