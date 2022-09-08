#ifndef ACTION_H
#define ACTION_H

#include "Common/Types.h"
#include "Concurrency/Atomic.h"

class Action
{
  public:
    Action()
        : mDone{ false }
    {
    }

    virtual ~Action() = default;

    virtual bool8 RunAction() = 0;

    bool8 IsDone() const noexcept { return mDone.Get(); }

  public:
    Atomic<bool8> mDone;
};

#endif
