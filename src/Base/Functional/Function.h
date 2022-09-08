#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>

// template <typename Fn>
// class Function;

template <typename Fn>
using Function = std::function<Fn>;

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;
using std::placeholders::_5;
using std::placeholders::_6;
using std::placeholders::_7;
using std::placeholders::_8;
using std::placeholders::_9;
using std::placeholders::_10;

template <typename... Args>
auto Bind( Args&&... args ) -> decltype( std::bind( std::forward<Args>( args )... ) )
{
    return std::bind( std::forward<Args>( args )... );
}

template <typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( Ret ( *const& fn )( Args... ) )
{
    return Function< Ret(Args...) >( fn );
}

template <typename Cls, typename Ret, typename... Args>
Function<Ret(Cls*, Args...)> MakeFunction( Ret ( Cls::*const& fn )( Args... ) )
{
    return Function<Ret(Cls*, Args...)>( fn );
}

template <typename Cls, typename Ret, typename... Args>
Function<Ret(Cls*, Args...)> MakeFunction( Ret ( Cls::*const& fn )( Args... ) const )
{
    return Function<Ret(Cls*, Args...)>( fn );
}

template <typename Obj, typename Cls, typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( Obj* obj, Ret ( Cls::*const& fn )( Args... ) )
{
    return Function<Ret(Args...)>( obj, fn );
}

template <typename Obj, typename Cls, typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( Obj* obj, Ret ( Cls::*const& fn )( Args... ) const )
{
    return Function<Ret(Args...)>( obj, fn );
}

template <typename Obj, typename Cls, typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( const std::shared_ptr<Obj>& obj, Ret ( Cls::* const& fn )(Args... ) )
{
    return Function<Ret(Args...)>( obj, fn );
}

template <typename Obj, typename Cls, typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( const std::shared_ptr<Obj>& obj, Ret ( Cls::* const& fn )( Args... ) const )
{
    return Function<Ret(Args...)>( obj, fn );
}

template <typename Ret, typename... Args>
Function<Ret(Args...)> MakeFunction( const Function<Ret(Args...)>& fn )
{
    return Function<Ret(Args...)>( fn );
}

/*namespace std
{
    template < typename Fn >
    void swap( Function< Fn >& lf, Function< Fn >& rf )
    {
        lf.Swap( rf );
    }
}*/

#endif