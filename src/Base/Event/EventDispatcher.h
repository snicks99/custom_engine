#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "Common/Platform.h"
#include "Memory/MemoryPool.h"
#include "Containers/Vector.h"
#include "Containers/Deque.h"
#include "Containers/Queue.h"
#include "Event/EventDefines.h"
#include "Debug/DBLAssert.h"

class IEvent;
class EventHandler;

using EventQueue = Vector<std::pair<IEvent*, void*>>;

CONSTEXPR_INLINE word_t DEFAULT_EVENT_DATA_SIZE{ 1 * MEMORY_KIBIBYTE };
CONSTEXPR_INLINE word_t MAX_EVENT_DATA{ 1000 };

class EventDispatcher
{
  public:
    EventDispatcher( const char8* name = "EventDispatcher" )
        : mPool{ DEFAULT_EVENT_DATA_SIZE, 1, sizeof( word_t ), name }
        , mEvtQueue{}
    {
        mEvtQueue.reserve( MAX_EVENT_DATA );
    }
    ~EventDispatcher();

    void QueueEvent( IEvent* evt, void* data )
    {
        mEvtQueue.emplace_back( evt, data );
    }

    /**
     * Careful trigger doesn't delete the data - niccco
     */
    void TriggerEvent( IEvent* evt, void* data );

    void DispatchEvents();

  protected:
    MemoryPool mPool;

    EventQueue mEvtQueue;
};

#endif
