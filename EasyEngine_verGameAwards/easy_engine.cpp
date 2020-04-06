// 作成者 : 板場
#include "easy_engine.hpp"
#include <Windows.h>
#include <tchar.h>
#include "application_status.hpp"
#include "keyboard.hpp"

// ウィンドウプロシージャ関数宣言
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

BEGIN_EGEG

// クラス定義
/*===========================================================================*/
struct EasyEngine::Impl
{
    HWND h_wnd_;
    std::unique_ptr<InputDeviceManager> input_device_manager_;
    std::unique_ptr<RenderingManager> rendering_manager_;
    JobScheduler<Job<void(uint64_t)>> task_manager;

    bool createWindow();
};


// 定数定義
/*===========================================================================*/
namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEX = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace


// 実体の宣言
/*===========================================================================*/
std::unique_ptr<EasyEngine::Impl> EasyEngine::p_impl_;


// EasyEngine 関数定義
/*===========================================================================*/
// エンジン初期化
DetailedReturnValue<bool> EasyEngine::initialize()
{
    using RetTy = DetailedReturnValue<bool>;

    // エンジンの実装部を生成
    try {
        p_impl_ = std::make_unique<Impl>();
    }
    catch ( const std::bad_alloc& e ) {
        return RetTy( false, e.what() );
    }

    // ウィンドウの生成＆表示
    if( p_impl_->createWindow() == false )
        return RetTy( false, "ウィンドウの生成に失敗" );
    ShowWindow( p_impl_->h_wnd_, SW_NORMAL );

    // 入力デバイスマネージャーを生成
    try {
        p_impl_->input_device_manager_ = InputDeviceManager::create();
    } catch( std::bad_alloc& e ) {
        return RetTy( false, e.what() );
    }

    // レンダリングマネージャ―を生成
    try {
        p_impl_->rendering_manager_ = RenderingManager::create();
    } catch( const std::runtime_error& e ) {
        return RetTy( false, e.what() );
    } catch( const std::bad_alloc& e ) {
        return RetTy( false, e.what() );
    }


    return true;
};

// エンジン終了
void EasyEngine::finalize()
{
    p_impl_.reset( nullptr );
}

// ウィンドウハンドルの取得
HWND EasyEngine::getWindowHandle() noexcept
{
    return p_impl_->h_wnd_;
}

// 入力デバイスマネージャ―の取得
InputDeviceManager* EasyEngine::getInputDeviceManager() noexcept
{
    return p_impl_->input_device_manager_.get();
}

// レンダリングエンジンの取得
RenderingManager* EasyEngine::getRenderingManager() noexcept
{
    return p_impl_->rendering_manager_.get();
}

// タスクマネージャ―の取得
JobScheduler<Job<void(uint64_t)>>* EasyEngine::getTaskManager() noexcept
{
    return &p_impl_->task_manager;
}

// EasyEngine::Impl 関数定義
/*===========================================================================*/
// ウィンドウの作成
class WindowRegisterer
{
public :
    WindowRegisterer( const WNDCLASSEX& Wnd)
    {
        if (RegisterClassEx(&Wnd) == false) throw std::runtime_error( "ウィンドウの登録失敗。" );
    }
};
bool EasyEngine::Impl::createWindow()
{
    // ウィンドウを登録( 一度のみ実行 )
    static const WNDCLASSEX wnd =
    {
        sizeof( WNDCLASSEX ),
        CS_VREDRAW,
        WinProc,
        0,
        0,
        GetModuleHandle( nullptr ),
        0,
        LoadCursor( nullptr, IDC_ARROW ),
        reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 ),
        0,
        _T( "Abyabyabyabyabya" ),
        0
    };
    try {
        static WindowRegisterer regist( wnd );
    } catch ( const std::runtime_error& ) {
        return false;
    }

    // クライアント領域が解像度に合うよう、ウィンドウサイズを調整
    RECT region;
    region.left = region.top = 0L;
    region.right = kHorizontalResolution<long>;
    region.bottom = kVerticalResolution<long>;
    if( AdjustWindowRectEx(&region, kWindowStyle, false, kWindowStyleEX) == false )
        return false;

    // ウィンドウ作成
    h_wnd_ = CreateWindowEx(
        kWindowStyleEX,
        _T( "Abyabyabyabyabya" ),
        _T( "EasyEngine" ),
        kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        nullptr,
        nullptr,
        wnd.hInstance,
        nullptr);
    if( h_wnd_ == nullptr ) return false;

    return true;
}

END_EGEG

// WinProc 関数定義
/*===========================================================================*/
LRESULT CALLBACK WinProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC         hdc;

    switch( Message )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        return 0;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN :
        // Escキーの押下で終了する。
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

    case WM_KEYUP :
    case WM_SYSKEYUP :
        EGEG EasyEngine::getInputDeviceManager()->inputEventProcessing( Message, wParam, lParam );
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, Message, wParam, lParam );
}

// EOF
