#ifndef BOOST_FUNCTION_H
#define BOOST_FUNCTION_H

#include <boost/bind/bind.hpp>

template <typename... Args>
auto BoostBind( Args&&... args ) -> decltype( boost::bind( std::forward<Args>( args )... ) )
{
    return boost::bind( std::forward<Args>( args )... );
}

#endif