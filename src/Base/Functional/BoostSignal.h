#ifndef BOOST_SIGNAL_H
#define BOOST_SIGNAL_H

#include "Connection.h"

#include <boost/bind/bind.hpp>

constexpr int32 DEFAULT_SIGNAL_GROUP{ 0x3FFFFFFF };

template <typename... Args>
class Signal
{
	public:
		using SignalT = boost::signals2::signal<void ( Args... )>;

		Signal()
		{
		}

		virtual ~Signal()
		{
			signal.disconnect_all_slots();
		}

		boost::signals2::connection Connect( const typename SignalT::slot_type& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			return signal.connect( group, subscriber );
		}

		void Connect( Connection& connection, const typename SignalT::slot_type& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			connection = Connect( subscriber, group );
		}

		void Connect( ConnectionList& connections, const typename SignalT::slot_type& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			connections.emplace_back( Connect( subscriber, group ) );
		}

		void Emit( Args... args )
		{
			signal( args... );
		}

	protected:
		SignalT signal;
};

template <typename... Args>
class SignalUnsafe
{
	public:
		using DummyMutex = boost::signals2::keywords::mutex_type<boost::signals2::dummy_mutex>;
		using SignalT    = typename boost::signals2::signal_type<void ( Args... ), DummyMutex>::type;
		using Subscriber = typename SignalT::slot_type;

		SignalUnsafe()
		{
		}

		virtual ~SignalUnsafe()
		{
			signal.disconnect_all_slots();
		}

		boost::signals2::connection Connect( const Subscriber& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			return signal.connect( group, subscriber );
		}

		void Connect( Connection& connection, const Subscriber& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			connection = Connect( subscriber, group );
		}

		void Connect( ConnectionList& connections, const Subscriber& subscriber, const int32& group = DEFAULT_SIGNAL_GROUP )
		{
			connections.emplace_back( Connect( subscriber, group ) );
		}

		void Emit( Args... args )
		{
			signal( args... );
		}

	protected:
		SignalT signal;
};

#endif