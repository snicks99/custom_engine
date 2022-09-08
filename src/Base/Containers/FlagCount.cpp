#include "Containers/FlagCount.h"

FlagCount::FlagCount() :
    mFlags{ 0 },
    mCount{}
{
}

void FlagCount::AddFlag( uint32 flag )
{
    mFlags |= flag;

    for ( uint32 i{ 0 }; i < ARRAY_SIZE( mCount ) && flag; ++i )
    {
        uint32& count{ mCount[i] };

        uint32 id{ static_cast<uint32>( 0x01 << i ) };

        if ( flag & id )
        {
            ++count;
            flag &= ~id;
        }
    }
}

void FlagCount::RemoveFlag( uint32 flag )
{
    for ( uint32 i{ 0 }; i < ARRAY_SIZE( mCount ) && flag; ++i )
    {
        uint32& count{ mCount[i] };

        uint32 id{ static_cast<uint32>( 0x01 << i ) };

        if ( count == 0 )
        {
            flag &= ~id;
            continue;
        }

        if ( flag & id )
        {
            --count;
            flag &= ~id;

            if ( count == 0 )
            {
                mFlags &= ~id;
            }
        }
    }
}

bool FlagCount::HasFlags( uint32 flag ) const
{
    return ( mFlags & flag ) != 0;
}

uint32 FlagCount::GetFlags() const
{
    return mFlags;
}
