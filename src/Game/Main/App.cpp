#include "Main/ClientApp.h"

#include "Clock/SystemTime.h"
#include "Event/EventDispatcher.h"
#include "Log/Logger.h"

#include "Resource/DBLRscPakMgr.h"

#include "Helper/PluginRw.h"
#include "Texture/TexturePlugin.h"
#include "Clump/NtlAtomicPlugin.h"
#include "FileSystem/FSysPakRw.h"
#include "FileSystem/FSysPak2Rw.h"
#include "Profiler/Profiler.h"

#include "Application/DPIScale.h"
#include "Input/InputEvent.h"
#include "Input/InputMgr.h"
#include "RenderCamera/CameraMgr.h"

#include "NtlWorld/NtlWorldPlugin.h"
#include "NtlWorld/NtlWorldMaterialPlugin.h"
#include "NtlWorld/NtlPLMaterialExtPlugin.h"
#include "Resource/PLRscMgr.h"
#include "Entity/World/PLWorld.h"
#include "Entity/World/PLDummyWorld.h"
#include "Entity/Character/PLCharacter.h"

#include "resource.h"

#include <windowsx.h>

constexpr float32 DEFAULT_CAMERA_NEAR{ 0.5f };
constexpr float32 DEFAULT_CAMERA_FAR{ 512.0f };

ClientApp::ClientApp()
    : Application{}
    , mRenderCamera{}
    , mCharset{ nullptr }
    , mFgrColor{ 255, 255, 255, 255 }
    , mBgrColor{ 0, 0, 0, 0 }
    , mSceneMgr{}
    , mFramePeak{ 0 }
{
}

ClientApp::~ClientApp()
{
    mSceneMgr.Destroy();
    GetRscMgr().Destroy();

    if ( mCharset )
    {
        RtCharsetDestroy( mCharset );
        mCharset = nullptr;

        RtCharsetClose();
    }

    // SafeDelete( mRenderCamera );
    GetCameraMgr().SetRCamera( nullptr );
}

bool ClientApp::Create( HINSTANCE hInstance, LPCSTR windowName, int32 posX, int32 posY, int32 width, int32 height, WindowMode wndMode /*= WINDOW_MODE_WINDOW*/ )
{
    // const WindowMode wndMode{ static_cast<WindowMode>( storageSystem->GetIntData( STORAGE_GRAPHIC_WINDOW_MODE ) ) };

    // const int32 width{ static_cast<int32>( storageSystem->GetIntData( STORAGE_GRAPHIC_SELECT_VIDEOWIDTH ) ) };
    // const int32 height{ static_cast<int32>( storageSystem->GetIntData( STORAGE_GRAPHIC_SELECT_VIDEOHEIGHT ) ) };

    return Application::Create( hInstance, windowName, posX, posY, width, height, wndMode );
}

bool8 ClientApp::RegisterMainWindowClass( HINSTANCE hInstance )
{
    WNDCLASS windowClass;

#ifdef UNDER_CE
    windowClass.style = CS_DBLCLKS;
#else
    windowClass.style = CS_BYTEALIGNWINDOW | CS_DBLCLKS;
#endif

    windowClass.lpfnWndProc   = (WNDPROC)MainWndProc;
    windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;
    windowClass.hInstance     = hInstance;
    windowClass.hIcon         = ::LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );
    windowClass.hCursor       = ::LoadCursor( 0, IDC_ARROW );
    windowClass.hbrBackground = 0;
    windowClass.lpszMenuName  = 0;
    windowClass.lpszClassName = MainWindowClassName;

    return ::RegisterClass( &windowClass ) != 0;
}

bool ClientApp::AttachPlugin()
{
    VERIFY_ATTACH_PLUGIN( RwTexExtPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpWorldPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpPVSPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpCollisionPluginAttach );
    VERIFY_ATTACH_PLUGIN( RtAnimInitialize );
    VERIFY_ATTACH_PLUGIN( RpLtMapPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpHAnimPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpSkinPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpToonPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpUserDataPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpIdPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpMatFXPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpUVAnimPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpPTankPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpPrtStdPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpPrtAdvPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpNtlAtomicPluginAttach );
    VERIFY_ATTACH_PLUGIN( NtlMatExtPluginAttach );
    VERIFY_ATTACH_PLUGIN( RpNtlWorldAttach );
    VERIFY_ATTACH_PLUGIN( RpNtlWorldMaterialPluginAttach );

    return Application::AttachPlugin();
}

bool ClientApp::RegisterFileSystem()
{
    RwChar curDir[MAX_DIR_PATH]{};

    DWORD len{ GetCurrentDirectory( MAX_DIR_PATH, curDir ) };

    if ( len == 0 || len > MAX_DIR_PATH - 1 )
    {
        MGE_ERROR( false, "Can't get current directory" );
        return false;
    }

    strcat( curDir, "\\" );

    if ( FSysPak2Rw::Init( curDir ) == false )
        return false;

    return true;
}

#include "WorldFieldMgr.h"
#include "WFHelper.h"

void OfflineTest()
{
#if 0
    NtlWorldParam wp{};

    SerializeNtlWorldParam( "world/dbo_battle_001", wp );
    SerializeNtlWorldParam( "world/dbo_battle_002", wp );
    SerializeNtlWorldParam( "world/dbo_battle_003", wp );
    SerializeNtlWorldParam( "world/dbo_bdungeon_001", wp );
    SerializeNtlWorldParam( "world/dbo_bdungeon_002", wp );
    SerializeNtlWorldParam( "world/dbo_bdungeon_003", wp );
    SerializeNtlWorldParam( "world/dbo_bdungeon_004", wp );
    SerializeNtlWorldParam( "world/dbo_budoh_001", wp );
    SerializeNtlWorldParam( "world/dbo_budoh_002", wp );
    SerializeNtlWorldParam( "world/dbo_budoh_003", wp );
    SerializeNtlWorldParam( "world/dbo_cdungeon_001", wp );
    SerializeNtlWorldParam( "world/dbo_dojo_001", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_000", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_001", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_002", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_003", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_004", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_005", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_006", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_007", wp );
    SerializeNtlWorldParam( "world/dbo_dungeon_etc", wp );
    SerializeNtlWorldParam( "world/dbo_dwc_001", wp );
    SerializeNtlWorldParam( "world/dbo_green", wp );
    SerializeNtlWorldParam( "world/dbo_main_world", wp );
    SerializeNtlWorldParam( "world/dbo_main_world_02", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_001", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_002", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_003", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_004", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_005", wp );
    SerializeNtlWorldParam( "world/dbo_pdungeon_006", wp );
    SerializeNtlWorldParam( "world/dbo_quest_001", wp );
    SerializeNtlWorldParam( "world/dbo_quest_002", wp );
    SerializeNtlWorldParam( "world/dbo_quest_003", wp );
    SerializeNtlWorldParam( "world/dbo_quest_004", wp );
    SerializeNtlWorldParam( "world/dbo_quest_005", wp );
    SerializeNtlWorldParam( "world/dbo_quest_006", wp );
    SerializeNtlWorldParam( "world/dbo_quest_007", wp );
    SerializeNtlWorldParam( "world/dbo_select_character", wp );
    SerializeNtlWorldParam( "world/dbo_skdungeon_001", wp );
    SerializeNtlWorldParam( "world/dbo_start_001", wp );
    SerializeNtlWorldParam( "world/dbo_start_002", wp );
    SerializeNtlWorldParam( "world/dbo_start_003", wp );
    SerializeNtlWorldParam( "world/dbo_test", wp );
    SerializeNtlWorldParam( "world/dbo_tlq_001", wp );
    SerializeNtlWorldParam( "world/dbo_tlq_002", wp );
    SerializeNtlWorldParam( "world/dbo_tlq_003", wp );
    SerializeNtlWorldParam( "world/dbo_town_001", wp );
    SerializeNtlWorldParam( "world/dbo_town_002", wp );
    SerializeNtlWorldParam( "world/dbo_town_003", wp );
    SerializeNtlWorldParam( "world/dbo_wzone_001", wp );
#endif

#if 1
    // const Vec3D initialPos{ 4506.395f, -44.002f, 2517.439f };    // Login Screen
    const Vec3D initialPos{ 5876.743f, -89.051926f, 758.40576f };    // Korin
    // const Vec3D initialPos{ 3208.02173f, 23.8157902f, -2490.78003f };    // Namek
    // const Vec3D initialPos{ -1015.60547f, 62.7427864f, 2359.32886f };    // Yellow Map
    // const Vec3D initialPos{ -685.127014f, -19.7883568f, -2608.80933f };    // Red Map
    // const Vec3D initialPos{ -2820.20508f, -8.49982834f, 1277.03564f };    // Yellow Map - Animation Bug
    // const Vec3D initialPos{ 3206.86841f, -43.0666924f, -871.924438f };    // West beach

    const Vec3D lookAtOffset{ -0.418f, -0.004f, 0.909f };    // West beach

    PLWorld* world{ GetSceneMgr()->CreateWorld( "MainWorld", "world/dbo_main_world/", "texture/world/", initialPos ) };

    GetRscMgr().SetAsyncEnable( true );

    GetCameraMgr().SetFOV( 60.f );
    GetCameraMgr().SetPos( initialPos );
    GetCameraMgr().SetLookAt( initialPos + lookAtOffset );

    // PLCharacterCreate param{};

    // GetSceneMgr()->CreateEntity<PLCharacter>( "MOB", &param );
#endif
}

bool ClientApp::CreateSubSystem( int32 width, int32 height, bool zBuffer )
{
    // Load keyboard accelerators
    mHandleAccel = ::LoadAccelerators( nullptr, MAKEINTRESOURCE( IDR_MAIN_ACCEL ) );

    // Framework Layer
    MGE_ASSERT( Application::CreateSubSystem( width, height, zBuffer ) );

    GetRscPakMgr().LoadLocalizedHeader( "KOREA/" );

    const float32 nearClipPlane{ DEFAULT_CAMERA_NEAR };
    const float32 farClipPlane{ DEFAULT_CAMERA_FAR };

    if ( GetRenderCamera()->Create( width, height, zBuffer, nearClipPlane, farClipPlane ) == nullptr )
    {
        MGE_ERROR( false, "Can't create the render camera" );
        return false;
    }

    GetCameraMgr().SetRCamera( GetRenderCamera() );

    mCharset = RtCharsetCreate( &mFgrColor, &mBgrColor );
    if ( mCharset == nullptr )
    {
        MGE_ERROR( false, "Can't create RtCharset" );
        return false;
    }

    if ( mSceneMgr.Create() == false )
    {
        MGE_ERROR( false, "Can't create SceneMgr" );
        return false;
    }

    SetRenderEnable( true );

#if 1
    /** offline test - niccco */
    OfflineTest();
#endif

    return true;
}

LRESULT ClientApp::PreTranslateMessage( HWND window, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT ret{ S_OK };

    switch ( message )
    {
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            const uint32 key{ static_cast<uint32>( wParam ) };
            const uint32 flags{ static_cast<uint32>( lParam ) };
            const bool8  press{ message == WM_KEYDOWN };

#if 0
            /** first we queue the key msg, in case some system needs it - niccco */
            KeyInput* keyInputEvt{ new KeyInput{} };

            keyInputEvt->mKey      = key;
            keyInputEvt->mFlags    = flags;
            keyInputEvt->mPress    = press;
            keyInputEvt->mTimestep = SystemTime::GetGameClockS();

            GetUpdateDispatcher().QueueEvent( &gKeyInputEvt, keyInputEvt );
#endif

            GetInputMgr().HandleKey( key, flags, press );

            /** delete this - niccco */
            if ( key == VK_CAPITAL )
            {
                mFramePeak = 0.0f;
            }
        }
        break;
        case WM_MOUSEMOVE:
        {
            GetInputMgr().HandleMouseMove( static_cast<uint32>( wParam ), DPIScale::PixelToDips( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ) );
        }
        break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        {
            const bool8 press{ message == WM_LBUTTONDOWN };

            if ( press )
            {
                ::SetCapture( GetHWnd() );
            }
            else
            {
                ::ReleaseCapture();
            }

            GetInputMgr().HandleMouseButton( static_cast<uint32>( wParam ), DPIScale::PixelToDips( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ), MOUSE_BUTTON_LEFT, false, press );
        }
        break;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        {
            const bool8 press{ message == WM_RBUTTONDOWN };

            if ( press )
            {
                ::SetCapture( GetHWnd() );
            }
            else
            {
                ::ReleaseCapture();
            }

            GetInputMgr().HandleMouseButton( static_cast<uint32>( wParam ), DPIScale::PixelToDips( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) ), MOUSE_BUTTON_RIGHT, false, press );
        }
        break;
    }

    return ret;
}

bool ClientApp::Resize( int32 width, int32 height, bool zBuffer, bool restoreFromMinimize )
{
    Application::Resize( width, height, zBuffer, restoreFromMinimize );

    RenderCamera* const renderCamera{ GetRenderCamera() };

    if ( renderCamera == nullptr )
        return false;

    if ( renderCamera->GetRWCamera() == nullptr )
        return false;

    /** maybe we should check for bigger numbers than 0 and return false? - niccco */
    if ( width == 0 || height == 0 )
        return false;

    RwRect rt{ 0, 0, width, height };

    renderCamera->SetCameraSize( &rt );

    if ( mWndHandle )
    {
        ::InvalidateRect( mWndHandle, nullptr, false );
    }

    return true;
}

RenderCamera* ClientApp::GetRenderCamera()
{
    return &mRenderCamera;
}

void ClientApp::DisplayFPS( float32 dt )
{
    char8 buffer[256]{ '\0' };

    mFramePeak = std::max( dt, mFramePeak );

    rwsprintf( buffer, "FPS: %0.2f", GetFPS() );
    RtCharsetPrint( mCharset, buffer, 0, 0 );

    rwsprintf( buffer, "FrameMS: %0.2f - %0.2f", dt * 1000.0f, mFramePeak * 1000.0f );
    RtCharsetPrint( mCharset, buffer, 0, 20 );

    rwsprintf( buffer, "Poly: %u", RW::gRenderPolyCnt );
    RtCharsetPrint( mCharset, buffer, 0, 40 );

    rwsprintf( buffer, "WSector - Atomic: %u - %u", RW::gRenderWSector, RW::gRenderAtomic );
    RtCharsetPrint( mCharset, buffer, 0, 60 );
}

bool ClientApp::Update( float32 dt )
{
    PROFILE_OPTICK_SCOPE( "Update", Optick::Category::GameLogic );

    Application::Update( dt );

    // RecvPackets
    // CoreUpdate
    // VisualUpdate
    mSceneMgr.Update( dt );

    return true;
}

bool ClientApp::Render( float32 dt, float32 alpha )
{
    PROFILE_OPTICK_SCOPE( "Render", Optick::Category::Rendering );

    RenderCamera* const renderCamera{ GetRenderCamera() };

    Application::Render( dt, alpha );

    mSceneMgr.UpdateBeforeCamera( dt );

    if ( GetRenderEnable() )
    {
        GetCameraMgr().Update( dt, alpha );

        if ( renderCamera->CameraClear( &mBgrColor, rwCAMERACLEARIMAGE | rwCAMERACLEARZ ) )
        {
            if ( renderCamera->PostCameraBeginUpdate( dt ) )
            {
                // if ( IsIconic( mWndHandle ) == false )
                {
                    mSceneMgr.Render( dt, alpha );
                }

                RwD3D9SetVertexShader( nullptr );
                RwD3D9SetPixelShader( nullptr );

                renderCamera->PostCameraEndUpdate();
            }
            else
            {
                /** this is never called, hmmm - niccco */
                // GetNtlGuiManager()->Update( dt, elapsedTime );
            }

            renderCamera->UpdatePostFX( dt );

            if ( renderCamera->MainCameraBeginUpdate( dt ) )
            {
                // if ( IsIconic( mWndHandle ) == false )
                {
                    // mVisualMgr->PostRender();
                    // mStageMgr->PostRender();

                    DisplayFPS( dt );
                }

                renderCamera->MainCameraEndUpdate();
            }

            renderCamera->CameraShowRaster( GetHWnd(), IsVSyncEnabled() ? rwRASTERFLIPWAITVSYNC : rwRASTERFLIPDONTWAIT );
        }
    }

    GetRscMgr().Update( dt );

    return true;
}
