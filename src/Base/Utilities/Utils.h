#ifndef UTILS_H
#define UTILS_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"
#include "Containers/Vector.h"

CONSTEXPR_INLINE char8 cToLower( char8 const& c )
{
    return ( c >= 'A' && c <= 'Z' ) ? c + ( 'a' - 'A' ) : c;
}

namespace Util
{
    void ReverseMemory( uint8* mem, size_t len );
    void MemXOR( uint8* mem, size_t memSize, const uint8* xorKey, size_t xorSize );

    void EncodeToUTF8( const char16* wstr, size_t size, String& str );
    void EncodeToUTF8( const WideString& wstr, String& str );

    void EncodeToUTF16( const char8* str, size_t size, WideString& wstr );
    void EncodeToUTF16( const String& str, WideString& wstr );

    void CToLower( char8& c );

    template<size_t N>
    inline void ArrayToLower( char8 ( &c )[N] )
    {
        for ( size_t i{ 0 }; i < N && c[i]; ++i )
        {
            CToLower( c[i] );
        }
    }

    void StrToLower( String& str );

    void                          Tokenize( Vector<String>& output, const String& str, const String& delim, bool keepEmpty = true );
    void                          TokenizeView( Vector<StringView>& output, StringView str, const String& delim, bool keepEmpty = true );
    std::vector<std::string_view> Tokenize( std::string_view str, char sep, bool keepEmpty );

    const char8* ExtractFileName( const char8* filePath );
    const char8* ExtractFileName( const String& filePath );

    bool StringEqualI( std::string_view str1, std::string_view str2 );

    inline bool isNumeric( wchar_t wchar )
    {
        return ( wchar >= L'0' && wchar <= L'9' );
    }

    inline bool isNumeric( char c )
    {
        return ( c >= '0' && c <= '9' );
    }

    inline bool isNumeric( char const* str )
    {
        for ( char const* c = str; *c; ++c )
            if ( !isNumeric( *c ) )
                return false;

        return true;
    }

    inline bool isNumericOrSpace( wchar_t wchar )
    {
        return isNumeric( wchar ) || wchar == L' ';
    }

};    // namespace Util

#endif
