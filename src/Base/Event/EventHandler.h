#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Common/Platform.h"
#include "Containers/UnorderedSet.h"
#include "Event/EventDefines.h"

class IEvent;

using EventSubscription = UnorderedSet<IEvent*>;

/**
 * I don't like the way we handle this, but it's the only way for now - niccco
 */
class EventHandler
{
  public:
    virtual ~EventHandler();

    void Subscribe( IEvent* evt, uint32 priority = EVENT_PRIORITY_NORMAL );
    void Unsubscribe( IEvent* evt, bool notify = true );

    virtual void HandleEvent( EventID evtId, IEvent* evt, void* data ) = 0;

  protected:
    EventHandler() = default;

    EventSubscription mSubscriptions;
};

#endif
