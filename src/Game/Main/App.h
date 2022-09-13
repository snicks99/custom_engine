#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include "Application/Application.h"
#include "Camera/PostFXCamera.h"
#include "SceneMgr/PLSceneMgr.h"
#include "plugin/rtcharse.h"

class ClientApp : public Application
{
  public:
    ClientApp();
    virtual ~ClientApp();

    bool Create( HINSTANCE hInstance, LPCSTR windowName, int32 posX, int32 posY, int32 width, int32 height, WindowMode wndMode = WINDOW_MODE_WINDOW ) override;

    bool Resize( int32 width, int32 height, bool zBuffer, bool restoreFromMinimize ) override;

    RenderCamera* GetRenderCamera() override;

  protected:
    bool8 RegisterMainWindowClass( HINSTANCE hInstance ) override;

    bool AttachPlugin() override;
    bool RegisterFileSystem() override;
    bool CreateSubSystem( int32 width, int32 height, bool zBuffer ) override;

    LRESULT PreTranslateMessage( HWND window, UINT message, WPARAM wParam, LPARAM lParam ) override;

    void DisplayFPS( float32 dt );

    /************************************************************************/
    /*                              Update system                           */
    /************************************************************************/
    bool Update( float32 dt ) override;

    bool Render( float32 dt, float32 alpha ) override;

    /************************************************************************/
    /*                              Variables                               */
    /************************************************************************/
    PostFXCamera mRenderCamera;

    RtCharset* mCharset;
    RwRGBA     mFgrColor;
    RwRGBA     mBgrColor;

    PLSceneMgr mSceneMgr;

    float32 mFramePeak;
};

#endif
