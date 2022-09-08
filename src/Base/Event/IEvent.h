#ifndef IEVENT_H
#define IEVENT_H

#include "Common/Defines.h"
#include "Containers/List.h"
#include "Event/EventDefines.h"
#include "Debug/DBLAssert.h"

class EventHandler;

/** p stands for priority */
using EventPPair = std::pair<EventHandler*, uint32 /** priority */>;
using EventPList = List<EventPPair>;

#define EVENT_CLASS( type )                                                          \
    static consteval EventID GetStaticType() { return HashEventID( #type ); }        \
    constexpr EventID        GetEventID() const override { return GetStaticType(); } \
    constexpr const char8*   GetName() const override { return #type; }

#define EVENT_CLASS_DELETE_CHECK( type )                                                                \
    virtual ~type() { DBL_ASSERT( mSubscribers.empty(), "Event %s has subscribers left", GetName() ); } \
    static consteval EventID GetStaticType() { return HashEventID( #type ); }                           \
    constexpr EventID        GetEventID() const override { return GetStaticType(); }                    \
    constexpr const char8*   GetName() const override { return #type; }

class IEvent
{
  public:
    virtual ~IEvent();

    constexpr virtual EventID      GetEventID() const = 0; /** change this to GetEventType() ? - niccco */
    constexpr virtual const char8* GetName() const    = 0;

    void Subscription( EventHandler* evtHdl, uint32 priority = EVENT_PRIORITY_NORMAL )
    {
        /** in theory subscription only happen once, but let's play safe - niccco */
#if 1
        auto it{
            std::find_if( mSubscribers.begin(), mSubscribers.end(), [&evtHdl]( const EventPPair& pair )
                          { return evtHdl == pair.first; } )
        };

        if ( it != mSubscribers.end() )
            return;
#endif

        mSubscribers.emplace_back( std::make_pair( evtHdl, priority ) );

        mSubscribers.sort( PairSecondGreater() );
    }

    void Unsubscription( EventHandler* evtHdl )
    {
        mSubscribers.remove_if( [&evtHdl]( const EventPPair& pair )
                                { return evtHdl == pair.first; } );
    }

    void DispatchEvent( void* data );

  protected:
    IEvent();

    EventPList mSubscribers;
};

#endif
