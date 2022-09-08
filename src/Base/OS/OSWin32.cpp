#include "OS/OS.h"
#include "Debug/DBLAssert.h"

#if DBL_PLATFORM == DBL_PLATFORM_WINDOWS

#    include <timeapi.h>

bool8 IsWindows11OrGreater()
{
    typedef void( WINAPI * RtlGetVersion_FUNC )( OSVERSIONINFOEXW* );

    bool8 ret{ false };

    HMODULE            hMod{ LoadLibrary( TEXT( "ntdll.dll" ) ) };
    RtlGetVersion_FUNC fnRtlGetVersion{};
    if ( hMod )
    {
        fnRtlGetVersion = (RtlGetVersion_FUNC)GetProcAddress( hMod, "RtlGetVersion" );
        if ( fnRtlGetVersion == 0 )
        {
            FreeLibrary( hMod );
            return ret;
        }

        OSVERSIONINFOEXW osvi{ sizeof( osvi ), 0, 0, 0, 0, { 0 }, 0, 0 };

        fnRtlGetVersion( &osvi );

        ret = osvi.dwMajorVersion >= HIBYTE( _WIN32_WINNT_WIN10 ) && osvi.dwMinorVersion >= LOBYTE( _WIN32_WINNT_WIN10 ) && osvi.dwBuildNumber >= 22000;

        FreeLibrary( hMod );
    }

    return ret;
}

void OS::Initialize()
{
    HMODULE hntdll = GetModuleHandle( "ntdll.dll" );
    if ( hntdll && (void*)GetProcAddress( hntdll, "wine_get_version" ) )
    {
        DBL_LOG_MESSAGE( "OS: WINE" );
    }
    else if ( IsWindows11OrGreater() )
    {
        DBL_LOG_MESSAGE( "OS: Win11" );
    }
    else if ( IsWindows10OrGreater() )
    {
        DBL_LOG_MESSAGE( "OS: Win10" );
    }
    else if ( IsWindows8Point1OrGreater() )
    {
        DBL_LOG_MESSAGE( "OS: Win8.1" );
    }
    else if ( IsWindows8OrGreater() )
    {
        DBL_LOG_MESSAGE( "OS: Win8" );
    }
    else if ( IsWindows7OrGreater() || IsWindows7SP1OrGreater() )
    {
        DBL_LOG_MESSAGE( "OS: Win7" );
    }
    else
    {
        DBL_LOG_MESSAGE( "OS: Unknown - unsupported Windows version" );
    }

    // set minimum resolution for periodic timers, otherwise Sleep(n) may wait at least as
    //  long as the windows scheduler resolution (~16-30ms) even for calls like Sleep(1) - godot
    timeBeginPeriod( 1 );
}

void OS::Finalize()
{
    timeEndPeriod( 1 );
}

#endif
