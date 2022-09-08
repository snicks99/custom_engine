#include "Clock/SystemTime.h"

ClockType SystemTime::mStartClock{ 0 };
ClockType SystemTime::mGameClock{ 0 };
float32   SystemTime::mGameClockS{ 0 };

ClockType SystemTime::Now()
{
    ClockType now{ 0 };

    GET_TIMESTAMP( now );

    return now - mStartClock;
}

void SystemTime::Update()
{
    SetGameClock( GetUs() );
}

void SystemTime::SetGameClock( ClockType now )
{
    mGameClock  = now;
    mGameClockS = CONVERT_US_TO_S( now );
}

ClockType SystemTime::GetGameClock()
{
    return mGameClock;
}

float32 SystemTime::GetGameClockS()
{
    return mGameClockS;
}
