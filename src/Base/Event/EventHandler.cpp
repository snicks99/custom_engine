#include "Event/IEvent.h"
#include "Event/EventHandler.h"
#include "Event/EventMgr.h"

EventHandler::~EventHandler()
{
    for ( auto it{ mSubscriptions.begin() }; it != mSubscriptions.end(); ++it )
    {
        IEvent* evt{ *it };

        evt->Unsubscription( this );
    }
}

void EventHandler::Subscribe( IEvent* evt, uint32 priority /*= EVENT_PRIORITY_NORMAL*/ )
{
    evt->Subscription( this, priority );

    mSubscriptions.emplace( evt );
}

void EventHandler::Unsubscribe( IEvent* evt, bool notify /*= true*/ )
{
    if ( notify )
    {
        evt->Unsubscription( this );
    }

    mSubscriptions.erase( evt );
}
