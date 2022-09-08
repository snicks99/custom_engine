#ifndef EVENT_MGR_H
#define EVENT_MGR_H

#include "Memory/MemoryPool.h"
#include "Containers/List.h"
#include "Containers/UnorderedMap.h"
#include "Event/EventDefines.h"

class IEvent;
class EventHandler;

using EventUMap  = UnorderedMap<EventID, IEvent*>;
using EventQueue = List<std::pair<IEvent*, void*>>;

class EventMgr
{
  public:
    static EventMgr& Instance()
    {
        static EventMgr instance{};

        return instance;
    }

    ~EventMgr() = default;

    /** unused (prob remove) - niccco */
    void RegisterEvent( IEvent* evt );
    void ReleaseEvent( IEvent* evt );

    void RegisterEvtHdl( IEvent* evt, EventHandler* evtHdl );
    void ReleaseEvtHdl( IEvent* evt, EventHandler* evtHdl );

    template<typename T, typename... Args>
    T* QueueEvent( IEvent* evt, Args&&... args )
    {
        T* data{ new ( mPool.allocate( sizeof( T ) ) ) T( std::forward<Args>( args )... ) };

        mEvtQueue.emplace_back( std::make_pair( evt, data ) );

        return data;
    }

    void TriggerEvent( IEvent* evt, void* evtData );

    void DispatchEvents();

  protected:
    EventMgr();

    MemoryPool mPool;

    EventUMap  mEvents;
    EventQueue mEvtQueue;
};

#if 0
#    include <memory>

using EventSubscriber = EventSignal::Subscriber;
using EventUMap       = UnorderedMap<EventID, EventSignal>;
using EventQueue      = List<std::pair<EventSignal*, std::unique_ptr<EventData>>>;

class EventMgr
{
  public:
    EventMgr();
    virtual ~EventMgr();

    void RegisterEvent( const EventID& eventId );
    void UnRegisterEvent( const EventID& eventId );

    void DispatchEvents();

    void QueueEvent( const EventID& eventId, EventData* data );
    void QueueEvent( EventData* data );
    void TriggerEvent( const EventID& eventId, EventData* data );

    void RegisterToEvent( const EventID& eventId, Connection& connection, const EventSubscriber& subscriber, const int32 group = DEFAULT_SIGNAL_GROUP );
    void RegisterToEvent( const EventID& eventId, ConnectionList& connectionList, const EventSubscriber& subscriber, const int32 group = DEFAULT_SIGNAL_GROUP );

  protected:
    EventUMap  mEvents;
    EventQueue mEventQueue;
};

#    define sEventMgr EventMgr::Instance()

#    define REGISTER_TO_EVENT( eventId, connection, subscriber, group ) sEventMgr->RegisterToEvent( eventId, connection, subscriber, group )
#endif

#endif
