// 作成者 : 板場

#include "application.hpp"
#include <Windows.h>
#include "game.hpp"


// ウィンドウプロシージャ
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

// unnamed namespace
/*===========================================================================*/
namespace
{
    constexpr long kClinntWidth  = 1280L;
    constexpr long kClientHeight = 720L;
    const HBRUSH kBackgroundColor = reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 );
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace

BEGIN_EG_EG

// 実装クラスの定義
/*===========================================================================*/
class Application::Impl
{
public:
    bool initialize();
    void finalize();

    HWND h_window_;
};


// 関数の実装
/*===========================================================================*/
// Ctor
Application::Application() :
    p_impl_( std::make_unique<Impl>() )
{
}

// インスタンスの返却( pimplイディオムを使用しているため、インライン化できない )
Application* Application::instance()
{
    static Application i;
    return &i;
}

// 実行処理
void Application::execute()
{
    // アプリケーションの初期化
    if( p_impl_->initialize() == false ) return;

    // ゲームの実行
    Game game;
    game.execute();

    // アプリケーションの終了
    p_impl_->finalize();
}

// アプリケーション初期化処理
//
// アプリケーションの初期化に必要な処理を実行する。
//
// 初期化に成功した場合　true
// 初期化に失敗した場合　false を戻り値として返却する。
bool Application::Impl::initialize()
{
    // ウィンドウの登録
    WNDCLASSEX wnd = {};
    wnd.cbSize        = sizeof( WNDCLASSEX );
    wnd.style         = CS_VREDRAW;
    wnd.hInstance     = GetModuleHandle( nullptr );
    wnd.lpszClassName = "Game_MainWindow";
    wnd.hCursor       = LoadCursor( nullptr, IDC_ARROW );
    wnd.hbrBackground = reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 );
    wnd.lpfnWndProc   = WinProc;
    if( RegisterClassEx( &wnd ) == false ) return false;

    // ウィンドウの作成
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = kClinntWidth;
    rect.bottom = kClientHeight;
    AdjustWindowRectEx( &rect, kWindowStyle, false, kWindowStyleEx );

    h_window_ = CreateWindowEx(
        kWindowStyleEx,
        wnd.lpszClassName,
        "Game",
        kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        wnd.hInstance,
        nullptr
    );
    if( h_window_ == nullptr ) return false;

    ShowWindow( h_window_, SW_NORMAL );

    return true;
}

// アプリケーション終了処理
//
// 必要に応じて開放処理を行う
void Application::Impl::finalize()
{

}

END_EG_EG

// ウィンドウプロシージャ実装
/*===========================================================================*/
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC         hdc;

    switch( Msg )
    {
    case WM_PAINT :
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        
        return 0;
    case WM_KEYDOWN :
        // Escキーの押下で終了する
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

        return 0;
    case WM_DESTROY :
        PostQuitMessage( 0 );
        return 0;
    }

    // その他のメッセージ処理
    return DefWindowProc( hWnd, Msg, wParam, lParam );
}
// EOF
