#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

#include "Clock/TimeType.h"

class SystemTime
{
  public:
    static void Init();

    static ClockType Now();
    static ClockType GetUs();
    static ClockType TimestampToUs( ClockType timestamp );

    static void Update();

    static void      SetGameClock( ClockType now );
    static ClockType GetGameClock();
    static float32   GetGameClockS();

  private:
    static ClockType mStartClock;
    static ClockType mGameClock;
    static float32   mGameClockS;
};

#endif
