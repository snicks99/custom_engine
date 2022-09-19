#ifndef FACTORY_H
#define FACTORY_H

#include "Common/Types.h"
#include "Containers/UnorderedMap.h"
#include "Hash/String/StringID.h"
#include "Debug/MGEAssert.h"

#define FACTORY_PRODUCT( T, MACHINE )                                          \
    static consteval StringID GetStaticType() { return HashStringExpr( #T ); } \
    static constexpr MACHINE* Product() { return new T{}; }

template<typename T>
class Factory
{
  public:
    using CreateFn = T* (*)();

    template<typename P>
    void Register()
    {
        const StringID typeId{ P::GetStaticType() };

        auto it{ mMachine.find( typeId ) };
        if ( it != mMachine.end() )
        {
            MGE_ERROR( false, "Factory type %u is duplicated", typeId );
            return;
        }

        mMachine.emplace( typeId, std::move( P::Product ) );
    }

    template<typename P>
    void Register( CreateFn fn )
    {
        const StringID typeId{ P::GetStaticType() };

        auto it{ mMachine.find( typeId ) };
        if ( it != mMachine.end() )
        {
            MGE_ERROR( false, "Factory type %u is duplicated", typeId );
            return;
        }

        mMachine.emplace( typeId, std::move( fn ) );
    }

    constexpr T* Create( StringID typeId ) const noexcept
    {
        auto it{ mMachine.find( typeId ) };
        if ( it == mMachine.end() )
        {
            MGE_ERROR( false, "Type %u not found in the factory", typeId );
            return nullptr;
        }

        return it->second();
    }

    template<typename P>
    constexpr P* Create() const noexcept
    {
        const StringID typeId{ P::GetStaticType() };

        return reinterpret_cast<P*>( Create( typeId ) );
    }

  protected:
    UnorderedMap<StringID, CreateFn> mMachine;
};

#endif
