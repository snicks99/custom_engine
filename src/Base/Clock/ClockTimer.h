#ifndef CLOCK_TIMER_H
#define CLOCK_TIMER_H

/**
 * Timer's related to clock SystemTime - niccco
 */
#include "Clock/SystemTime.h"

/**
    GameTimer it's a timer for events that need a consistent time the whole Tick function.

    Cooldown in game (buff, skills, etc), can't use real time because it can expire in the middle of the execution,
        neither can use frame delta time because it's cap, and those are time sensitive.
*/
class GameTimer
{
  public:
    explicit GameTimer( ClockType expiration )
        : mExpireTime{ expiration + SystemTime::GetGameClock() }
    {
    }

    ~GameTimer() = default;

    bool8 HasExpired() const noexcept { return SystemTime::GetGameClock() >= mExpireTime; }
    bool8 IsTimeleft() const noexcept { return mExpireTime > SystemTime::GetGameClock(); }

    ClockType GetTime() const noexcept { return mExpireTime; }

  protected:
    ClockType mExpireTime;
};

/**
    RealTimer it's a timer for events attached to real time.

    Setting a max time per function, we can't use game clock, we need the real time.
*/
class RealTimer
{
  public:
    explicit RealTimer( ClockType expiration )
        : mExpireTime{ expiration + SystemTime::GetUs() }
    {
    }

    ~RealTimer() = default;

    bool8 HasExpired() const noexcept { return SystemTime::GetUs() >= mExpireTime; }
    bool8 IsTimeleft() const noexcept { return mExpireTime > SystemTime::GetUs(); }

    ClockType GetTime() const noexcept { return mExpireTime; }

  protected:
    ClockType mExpireTime;
};

#endif
