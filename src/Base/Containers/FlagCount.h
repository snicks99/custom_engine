#ifndef FLAG_COUNT_H
#define FLAG_COUNT_H

#include "Common/Defines.h"

class FlagCount
{
  public:
    FlagCount();
    ~FlagCount() = default;

    void AddFlag( uint32 flag );
    void RemoveFlag( uint32 flag );

    bool HasFlags( uint32 flag ) const;

    uint32 GetFlags() const;

  protected:
    uint32 mFlags;
    uint32 mCount[32];
};

#endif
