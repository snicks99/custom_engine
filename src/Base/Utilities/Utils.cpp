#include "Utils.h"
#include <string.h>
#include <algorithm>

namespace Util
{
    void ReverseMemory( uint8* mem, size_t len )
    {
        std::reverse( mem, mem + len );
    }

    void MemXOR( uint8* mem, size_t memSize, const uint8* xorKey, size_t xorSize )
    {
        if ( mem == nullptr || memSize == 0 )
            return;

        if ( xorKey == nullptr || xorSize == 0 )
            return;

        for ( size_t i{ 0 }, xorI{ 0 }; i < memSize; ++i, ++xorI %= xorSize )
            mem[i] ^= xorKey[xorI];
    }

    void CToLower( char8& c )
    {
        c = static_cast<char8>( std::tolower( c ) );
    }

    void StrToLower( String& str )
    {
        std::transform( str.begin(), str.end(), str.begin(), []( unsigned char c )
                        { return std::tolower( c ); } );
    }

    void Tokenize( Vector<String>& tokens, const String& str, const String& delim, bool keepEmpty /*= true*/ )
    {
        size_t start{ 0 };

        for ( auto end{ str.find( delim.c_str() ) };
              end != String::npos;
              end = str.find( delim.c_str(), start ) )
        {
            if ( keepEmpty || ( start < end ) )
                tokens.push_back( str.substr( start, end - start ) );

            start = end + 1;
        }

        if ( keepEmpty || ( start < str.length() ) )
            tokens.push_back( str.substr( start ) );
    }

    void TokenizeView( Vector<StringView>& tokens, StringView str, const String& delim, bool keepEmpty /*= true*/ )
    {
        size_t start{ 0 };

        for ( auto end{ str.find( delim.c_str() ) };
              end != StringView::npos;
              end = str.find( delim.c_str(), start ) )
        {
            if ( keepEmpty || ( start < end ) )
                tokens.push_back( str.substr( start, end - start ) );

            start = end + 1;
        }

        if ( keepEmpty || ( start < str.length() ) )
            tokens.push_back( str.substr( start ) );
    }

    const char8* ExtractFileName( const char8* filePath )
    {
        int32 len{ static_cast<int32>( strlen( filePath ) ) - 1 };

        while ( len >= 0 )
        {
            if ( filePath[len] == '\\' || filePath[len] == '/' )
                return filePath + len + 1;

            --len;
        };

        return filePath;
    }

    const char8* ExtractFileName( const String& filePath )
    {
        const char8* ret{ filePath.c_str() };

        return ExtractFileName( ret );
#if 0
        int32 len{ static_cast<int32>( filePath.size() ) - 1 };

        while ( len >= 0 )
        {
            if ( ret[len] == '\\' || ret[len] == '/' )
                return ret + len + 1;

            --len;
        };

        return ret;
#endif
    }

    bool StringEqualI( std::string_view a, std::string_view b )
    {
        return std::equal( a.begin(), a.end(), b.begin(), b.end(), []( char c1, char c2 )
                           { return std::tolower( c1 ) == std::tolower( c2 ); } );
    }
}    // namespace Util
