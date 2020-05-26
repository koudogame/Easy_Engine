// 作成者 : 板場
/******************************************************************************

	include

******************************************************************************/
#include "engine.hpp"
#include <tchar.h>
#include "application_status.hpp"


BEGIN_EGEG

/******************************************************************************

    constant

******************************************************************************/
namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
    constexpr RECT  kWindowRegion{ 0L, 0L, kWindowWidth<long>, kWindowHeight<long> };
}


/******************************************************************************

    declaration & definition

******************************************************************************/
 // コールバック関数前方宣言
LRESULT CALLBACK winProc( HWND, UINT, WPARAM, LPARAM );

 // EasyEngineメンバ変数定義
HWND EasyEngine::window_handle_ = 0;
std::unique_ptr<EasyEngine::TaskManagerType> EasyEngine::task_manager_{};
std::unique_ptr<InputDeviceManager> EasyEngine::input_device_manager_{};
std::unique_ptr<RenderingManager> EasyEngine::rendering_manager_{};
std::unique_ptr<LevelManager> EasyEngine::level_manager_{};


/******************************************************************************

	EasyEngine

******************************************************************************/
 // コンストラクタ
EasyEngine::EasyEngine()
{
    
}


 // 初期化
DetailedReturnValue<bool> EasyEngine::initialize()
{
    auto ret = initializeWindow();
    if( !ret )  return ret;

    ret = initializeManager();
    if( !ret ) return ret;

	return Success{};
}


 // 終了処理
void EasyEngine::finalize()
{
    level_manager_.reset();
    rendering_manager_.reset();
    input_device_manager_.reset();
    task_manager_.reset();
}


// ウィンドウ初期化
DetailedReturnValue<bool> EasyEngine::initializeWindow()
{
    const WNDCLASSEX wndclassex
    {
        sizeof( WNDCLASSEX ),
        CS_VREDRAW,
        winProc,
        0,
        0,
        GetModuleHandle( nullptr ),
        0,
        LoadCursor( nullptr, IDC_ARROW ),
        reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1),
        0,
        _T( "Abyabyabyabyabya" ),
        0
    };
    if( !RegisterClassEx(&wndclassex) ) 
        return { Failure{}, "ウィンドウの登録に失敗しました。" };

    RECT region = kWindowRegion;
    if( !AdjustWindowRectEx(&region, kWindowStyle, false, kWindowStyleEx) )
        return { Failure{}, "ウィンドウサイズの調整に失敗しました。" };
    window_handle_ = CreateWindowEx(
        kWindowStyleEx,
        _T( "Abyabyabyabyabya"),
        _T( "EasyEngine" ),
        kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        nullptr,
        nullptr,
        wndclassex.hInstance,
        nullptr
    );
    if( !window_handle_ ) 
        return { Failure{}, "ウィンドウの生成に失敗しました。" };

    ShowWindow( window_handle_, SW_NORMAL );
    return Success{};
}


 // マネージャー初期化
 //
 // note : 生成順番に依存関係がある。
DetailedReturnValue<bool> EasyEngine::initializeManager()
{
    task_manager_ = std::make_unique<TaskManagerType>();

    input_device_manager_ = InputDeviceManager::create();
    if( !input_device_manager_ )
        return { Failure{}, "入力デバイスマネージャーの生成に失敗しました。" };

    rendering_manager_ = RenderingManager::create();
    if( !rendering_manager_ )
        return { Failure{}, "描画マネージャーの生成に失敗しました。" };

    level_manager_ = LevelManager::create();
    if( !level_manager_ )
        return { Failure{}, "レベルマネージャ―の生成に失敗しました。" };
    
    return Success{};
}


/******************************************************************************

	others

******************************************************************************/
 // コールバック関数
LRESULT CALLBACK winProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
    switch( Message )
    {
    case WM_PAINT :
        {
        PAINTSTRUCT ps;
        BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        }
        return 0;

    case WM_KEYDOWN :
        // Escキーの入力で終了する
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

    case WM_SYSKEYDOWN :
    case WM_KEYUP :
    case WM_SYSKEYUP :
        EasyEngine::getInputDeviceManager()->eventProcessing( Message, wParam, lParam );
        return 0;

    case WM_DESTROY :
        PostQuitMessage( 0 );
        return 0;

    default :
        return DefWindowProc( hWnd, Message, wParam, lParam );
    }
}

END_EGEG
// EOF
