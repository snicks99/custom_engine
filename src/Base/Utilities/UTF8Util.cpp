#include "Utilities/Utils.h"
#include "Debug/MGEAssert.h"
#include <utf8.h>

namespace Util
{

    void EncodeToUTF8( const char16* wstr, size_t size, String& str )
    {
        str.clear();
        str.reserve( size );

        try
        {
            utf8::utf16to8( wstr, wstr + size, std::back_inserter( str ) );
        }
        catch ( const std::exception& e )
        {
            MGE_ERROR( false, "UTF16->UTF8 conversion error: ", e.what() );
        }
    }

    void EncodeToUTF8( const WideString& wstr, String& str )
    {
        str.clear();
        str.reserve( wstr.size() );

        try
        {
            utf8::utf16to8( wstr.begin(), wstr.end(), std::back_inserter( str ) );
        }
        catch ( std::exception const& e )
        {
            MGE_ERROR( false, "UTF16->UTF8 conversion error: ", e.what() );
        }
    }

    void EncodeToUTF16( const char8* str, size_t size, WideString& wstr )
    {
        wstr.clear();
        wstr.reserve( size );

        try
        {
            utf8::utf8to16( str, str + size, std::back_inserter( wstr ) );
        }
        catch ( std::exception const& e )
        {
            MGE_ERROR( false, "UTF8->UTF16 conversion error: %s", e.what() );
        }
    }

    void EncodeToUTF16( const String& str, WideString& wstr )
    {
        wstr.clear();
        wstr.reserve( str.size() );

        try
        {
            utf8::utf8to16( str.begin(), str.end(), std::back_inserter( wstr ) );
        }
        catch ( std::exception const& e )
        {
            MGE_ERROR( false, "UTF8->UTF16 conversion error: %s", e.what() );
        }
    }

};    // namespace Util
