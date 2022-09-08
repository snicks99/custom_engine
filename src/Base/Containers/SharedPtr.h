#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "Common/Defines.h"
#include "Memory/MMU.h"

#define FWD_DECLARE_SHARED_PTR( type ) \
    class type;                        \
    using type##SPtr = SharedPtr<type>

#if ENABLE_STL_SHARED_PTR

#    include <memory>

template<typename T>
using SharedPtr = std::shared_ptr<T>;

#elif ENABLE_BOOST_SHARED_PTR

#    include <boost/shared_ptr.hpp>
#    include <boost/make_shared.hpp>

template<typename T>
using SharedPtr = boost::shared_ptr<T>;

template<class T, class... Args>
void CreateShared( SharedPtr<T>& sharedPtr, Args&&... args )
{
    sharedPtr = std::move( SharedPtr<T>{ new T{ boost::detail::sp_forward<Args>( args )... } } );
}

template<class Child, class T, class... Args>
void CreateChildShared( SharedPtr<T>& sharedPtr, Args&&... args )
{
    sharedPtr = std::move( SharedPtr<T>{ new Child{ boost::detail::sp_forward<Args>( args )... } } );
}

template<class T, class... Args>
void MakeShared( SharedPtr<T>& sharedPtr, Args&&... args )
{
    sharedPtr = boost::make_shared<T>( boost::detail::sp_forward<Args>( args )... );
}

#endif

#endif
