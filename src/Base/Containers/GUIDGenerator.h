#ifndef GUID_GENERATOR_H
#define GUID_GENERATOR_H

#include "Debug/DBLAssert.h"

using ObjectGUID = uint32;

CONSTEXPR_INLINE ObjectGUID INVALID_GUID{ 0xFFFFFFFF };

template<typename T>
class GUIDGenerator
{
  public:
    GUIDGenerator() :
        mGUID{ 1 }
    {
    }

    virtual ObjectGUID Generate()
    {
        if ( mGUID == INVALID_GUID )
        {
            DBL_ERROR( false, "GUID Generator %s overflow", typeid( T ).name() );
            return INVALID_GUID;
        }

        return mGUID++;
    }

  protected:
    ObjectGUID mGUID;
};

#endif
