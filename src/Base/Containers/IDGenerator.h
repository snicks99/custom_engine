#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include "Debug/MGEAssert.h"

using GenID = word_t;

CONSTEXPR_INLINE GenID INVALID_GEN_ID{ std::numeric_limits<word_t>::max() };

template<typename T>
class IDGenerator
{
  public:
    IDGenerator()
        : mID{ 0 }
    {
    }

    constexpr virtual GenID Generate()
    {
        if ( mID == INVALID_GEN_ID )
        {
            MGE_ERROR( false, "IDGenerator %s overflow", typeid( T ).name() );
            return INVALID_GEN_ID;
        }

        return mID++;
    }

  protected:
    GenID mID;
};

#endif
