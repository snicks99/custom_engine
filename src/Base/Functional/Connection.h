#ifndef CONNECTION_H
#define CONNECTION_H

#include "Containers/List.h"

#include <boost/signals2.hpp>

class Connection
{
  public:
    Connection() :
        connection{}
    {
    }

    explicit Connection( const boost::signals2::connection& r ) :
        connection{ r }
    {
    }

    const Connection& operator=( const boost::signals2::connection& r )
    {
        connection = r;

        return *this;
    }

  protected:
    boost::signals2::scoped_connection connection;
};

using ConnectionList = List<Connection>;

#endif
