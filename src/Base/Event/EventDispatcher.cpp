#include "Event/EventDispatcher.h"
#include "Event/IEvent.h"
#include "Event/EventHandler.h"

EventDispatcher ::~EventDispatcher()
{
    while ( mEvtQueue.empty() == false )
    {
        auto& it{ mEvtQueue.back() };

        void*& data{ it.second };

        SafeDelete( data );

        mEvtQueue.pop_back();
    }
}

void EventDispatcher::DispatchEvents()
{
    if ( mEvtQueue.empty() )
        return;

#if 0
    EventQueue evtQueue{};

    evtQueue.swap( mEvtQueue );

    for ( auto it{ evtQueue.begin() }; it != evtQueue.end(); ++it )
    {
        IEvent*& evt{ it->first };
        void*&   data{ it->second };

        evt->DispatchEvent( data );

        SafeDelete( data );
    }
#else
    while ( mEvtQueue.empty() == false )
    {
        auto& it{ mEvtQueue.back() };

        IEvent*& evt{ it.first };
        void*&   data{ it.second };

        evt->DispatchEvent( data );

        SafeDelete( data );

        mEvtQueue.pop_back();
    }
#endif
}

void EventDispatcher::TriggerEvent( IEvent* evt, void* data )
{
    evt->DispatchEvent( data );
}
