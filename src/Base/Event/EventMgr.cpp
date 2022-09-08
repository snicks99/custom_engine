#include "Event/EventMgr.h"
#include "Event/IEvent.h"

constexpr word_t DEFAULT_EVENT_DATA_SIZE{ 1 * MEMORY_KIBIBYTE };
constexpr word_t MAX_EVENT_DATA{ 64 };

EventMgr::EventMgr()
    : mPool{
        DEFAULT_EVENT_DATA_SIZE,
        MAX_EVENT_DATA,
        sizeof( word_t ),
        "EventMgr"
    }
    , mEvents{}
    , mEvtQueue{}
{
}

void EventMgr::RegisterEvent( IEvent* evt )
{
    mEvents.emplace( evt->GetEventID(), evt );
}

void EventMgr::ReleaseEvent( IEvent* evt )
{
    mEvents.erase( evt->GetEventID() );
}

void EventMgr::RegisterEvtHdl( IEvent* evt, EventHandler* evtHdl )
{
    evt->Subscription( evtHdl );
}

void EventMgr::ReleaseEvtHdl( IEvent* evt, EventHandler* evtHdl )
{
    evt->Unsubscription( evtHdl );
}

void EventMgr::DispatchEvents()
{
    EventQueue evtQueue{};

    evtQueue.swap( mEvtQueue );

    for ( auto it{ evtQueue.begin() }; it != evtQueue.end(); ++it )
    {
        IEvent* evt{ it->first };
        void*   evtData{ it->second };

        evt->DispatchEvent( evtData );
    }
}
