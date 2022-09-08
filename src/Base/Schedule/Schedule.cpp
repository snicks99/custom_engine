#include "Clock/SystemTime.h"
#include "Clock/ClockTimer.h"
#include "Schedule/Schedule.h"
#include "Debug/DBLAssert.h"

Scheduler::Scheduler()
    : mElements{}
    , mDT{ 0.0f }
{
}

Scheduler::~Scheduler()
{
}

ScheduleProcess Scheduler::Scheduling( float32 dt )
{
    if ( mElements.empty() )
    {
        mDT = 0.0f;

        return SCHEDULE_PROCESS_FINISH;
    }

    const RealTimer timer{ CONVERT_MS_TO_US( 1 ) };

    while ( timer.IsTimeleft() )
    {
        const ScheduleProcess res{ SchedulingProcess() };
        switch ( res )
        {
            case SCHEDULE_PROCESS_LOADING:
            case SCHEDULE_PROCESS_CONTINUE_NEXT:
            {
                return res;
            }
            break;
        }
    }

    return SCHEDULE_PROCESS_CONTINUE;
}

ScheduleProcess Scheduler::SchedulingProcess()
{
    ScheduleProcess ret{ SCHEDULE_PROCESS_CONTINUE };

    if ( mElements.empty() )
        return SCHEDULE_PROCESS_FINISH;

    ScheduleElement* element{ mElements.front() };

    if ( element )
    {
        switch ( element->mStep )
        {
            case ESCHEDULE_STEP_NONE:
            {
                element->mStep = ESCHEDULE_STEP_BEGIN;
            }
            case ESCHEDULE_STEP_BEGIN:
            {
                if ( !element->Begin() )
                {
                    RemovePresentSchedule();
                    break;
                }

                element->mStep = ESCHEDULE_STEP_SCHEDULING;
            }
            case ESCHEDULE_STEP_SCHEDULING:
            {
                auto process{ element->Scheduling() };

                if ( process != SCHEDULE_PROCESS_FINISH )
                {
                    ret = process;
                    break;
                }

                element->mStep = ESCHEDULE_STEP_END;
            }
            case ESCHEDULE_STEP_END:
            {
                element->End();
                RemovePresentSchedule();
            }
            break;
        }
    }

    return ret;
}

void Scheduler::RemovePresentSchedule()
{
    if ( mElements.empty() == false )
    {
        mElements.pop_front();
    }
}

void Scheduler::AddSchedule( ScheduleElement* scheduleElement )
{
    auto it{ std::find_if( mElements.begin(), mElements.end(), [&scheduleElement]( auto& element )
                           { return element->GetPrimaryKey() == scheduleElement->GetPrimaryKey(); } ) };

    if ( it != mElements.end() )
    {
        DBL_ERROR( false, "Duplicated schedule %d", scheduleElement->GetPrimaryKey() );
        SafeDelete( scheduleElement );
        return;
    }

    mElements.emplace_back( scheduleElement );
}

void Scheduler::RemoveSchedule( ScheduleID scheduleId )
{
    auto it{ std::find_if( mElements.begin(), mElements.end(), [&scheduleId]( auto& element )
                           { return element->GetPrimaryKey() == scheduleId; } ) };

    if ( it == mElements.end() )
        return;

    mElements.erase( it );
}

void Scheduler::ClearSchedule()
{
    mElements.clear();
}

ScheduleElement* Scheduler::GetFirstSchedule()
{
    if ( mElements.empty() )
        return nullptr;

    return mElements.front();
}

#if 0
/** deprecated old loading system - niccco */
{
mDT += dt;

while ( mDT > 0.0f )
{
    if ( auto firstSchedule{ GetFirstSchedule() } )
    {
        const float32 time{ mDT - firstSchedule->GetUsedTime() };
        if ( time >= 0.0f )
        {
            ScheduleProcess res{ SchedulingProcess() };
            switch ( res )
            {
                case SCHEDULE_PROCESS_LOADING:
                {
                    // mDT = firstSchedule->GetUsedTime();
                    mDT = time;
                }
                break;
                case SCHEDULE_PROCESS_CONTINUE:
                case SCHEDULE_PROCESS_FINISH:
                {
                    mDT = time;
                    continue;
                }
                break;
                case SCHEDULE_PROCESS_CONTINUE_NEXT:
                {
                    mDT = time;
                    return res;
                }
                break;
            }
        }
    }

    break;
}
}
#endif
