#include "Common/Platform.h"
#include "Log/Logger.h"
#include "Debug/DBLAssert.h"
#include "Main/ClientApp.h"

constexpr LPCSTR WindowName{ "Client" };

constexpr int32 DEFAULT_SCREEN_WIDTH{ 1024 };
constexpr int32 DEFAULT_SCREEN_HEIGHT{ 768 };

Logger gLogger{ "dbolog.txt" };

int APIENTRY WinMain( HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPSTR     lpCmdLine,
                      int       nCmdShow )
{
    ClientApp app{};

    if ( app.Create( hInstance, WindowName, 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, WINDOW_MODE_WINDOW ) == false )
    {
        DBL_ERROR( false, "Unable to create application" );
        return S_FALSE;
    }

    app.Run();

    return S_OK;
}
