#include "Event/IEvent.h"
#include "Event/EventHandler.h"
#include "Event/EventMgr.h"

IEvent::IEvent()
    : mSubscribers{}
{
}

IEvent::~IEvent()
{
    DBL_ASSERT( mSubscribers.empty(), "There are still subscribers" );

    for ( auto it{ mSubscribers.begin() }; it != mSubscribers.end(); ++it )
    {
        EventHandler* evtHdl{ it->first };

        evtHdl->Unsubscribe( this, false );
    }
}

void IEvent::DispatchEvent( void* data )
{
    for ( auto it{ mSubscribers.begin() }; it != mSubscribers.end(); ++it )
    {
        EventHandler* evtHdl{ it->first };

        evtHdl->HandleEvent( GetEventID(), this, data );
    }
}
