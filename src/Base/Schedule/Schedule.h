#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Common/Types.h"
#include "Containers/ScopedPtr.h"
#include "Containers/List.h"

class Scheduler;
class ScheduleElement;

enum ESCHEDULE_STEP
{
    ESCHEDULE_STEP_NONE = 0,
    ESCHEDULE_STEP_BEGIN,
    ESCHEDULE_STEP_SCHEDULING,
    ESCHEDULE_STEP_END,
};

enum ScheduleProcess
{
    SCHEDULE_PROCESS_LOADING = 0,

    SCHEDULE_PROCESS_CONTINUE,
    SCHEDULE_PROCESS_CONTINUE_NEXT,

    SCHEDULE_PROCESS_FINISH,
};

using ScheduleID = int32;

using ScheduleList = List<ScopedPtr<Scheduler>>;

class Scheduler
{
  public:
    Scheduler();
    virtual ~Scheduler();

    virtual ScheduleProcess Scheduling( float32 dt );
    virtual ScheduleProcess SchedulingProcess();
    virtual void            RemovePresentSchedule();

    virtual void AddSchedule( ScheduleElement* se );
    virtual void RemoveSchedule( ScheduleID scheduleId );
    virtual void ClearSchedule();

    virtual ScheduleElement* GetFirstSchedule();

  protected:
    List<ScopedPtr<ScheduleElement>> mElements;
    float32                          mDT;
};

class ScheduleElement
{
  public:
    friend class Scheduler;

    ScheduleElement( ScheduleID scheduleId, float32 usedTime )
        : mScheduleId{ scheduleId }
        , mUsedTime{ usedTime }
        , mStep{ ESCHEDULE_STEP_NONE }
    {
    }

    virtual ~ScheduleElement() {}

    virtual ScheduleID     GetPrimaryKey() const { return mScheduleId; }
    virtual float32        GetUsedTime() const { return mUsedTime; }
    virtual ESCHEDULE_STEP GetScheduleStep() const { return mStep; }

    virtual bool8           Begin()      = 0;
    virtual ScheduleProcess Scheduling() = 0;
    virtual bool8           End()        = 0;

  protected:
    ScheduleID     mScheduleId;
    float32        mUsedTime;
    ESCHEDULE_STEP mStep;
};

#endif
