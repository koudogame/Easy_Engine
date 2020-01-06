// 作成者 : 板場
#include "platform_windows.hpp"
#include <chrono>
#include "platform_factory.hpp"
#include "renderer_factory.hpp"
#include "renderer_d3d11.hpp"

// ウィンドウプロシージャ
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );
// プラットフォームのファクトリにPlatformWindowsを登録
ADD_PLATFORM( EG_EG PlatformID::kWindows, &PlatformWindows::create )


// unnamed namespace
/*===========================================================================*/
namespace
{
    constexpr long long kFramePerUS = 16666LL;

    constexpr long kWindowRegionWidth = 1280L;
    constexpr long kWindowRegionHeight = 720L;
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// 生成処理
IPlatform* PlatformWindows::create()
{
    PlatformWindows* i = new (std::nothrow) PlatformWindows();
    return i;
}

// 初期化処理
bool PlatformWindows::initialize()
{
    // ウィンドウの登録
    WNDCLASSEX wnd = {};
    wnd.cbSize        = sizeof( WNDCLASSEX );
    wnd.style         = CS_VREDRAW;
    wnd.hInstance     = GetModuleHandle( nullptr );
    wnd.lpszClassName = "Game_Abyabyabyabyabya";
    wnd.hCursor       = LoadCursor( nullptr, IDC_ARROW );
    wnd.hbrBackground = reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 );
    wnd.lpfnWndProc   = WinProc;
    if( RegisterClassEx( &wnd ) == false ) return false;
    

    // ウィンドウの作成
    RECT region;
    region.left = region.top = 0L;
    region.right = ::kWindowRegionWidth;
    region.bottom = ::kWindowRegionHeight;
    AdjustWindowRectEx( &region, ::kWindowStyle, false, ::kWindowStyleEx );

    window_handle_ = CreateWindowEx(
        ::kWindowStyleEx,
        wnd.lpszClassName,
        "Game",
        ::kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        nullptr,
        nullptr,
        wnd.hInstance,
        nullptr );
    if( window_handle_ == nullptr ) return false;

    // ウィンドウの表示
    ShowWindow( window_handle_, SW_NORMAL );

    return true;
}

// 終了処理
void PlatformWindows::finalize()
{

}

// ゲームループ
void PlatformWindows::gameLoop( std::function<bool(long long)> pFunc )
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;

    MSG msg = {};
    while( msg.message != WM_QUIT )
    {
        // メッセージ処理
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // ゲーム処理
        else
        {
            // フレームレート制御
            curr_time = high_resolution_clock::now();
            auto erapsed_time = curr_time - last_time;
            if( duration_cast<microseconds>(erapsed_time).count() >= ::kFramePerUS )
            {
                last_time = curr_time;

                if( !pFunc(duration_cast<milliseconds>(erapsed_time).count()) )
                    break;
#ifdef _DEBUG
                long long erapsed_ms = duration_cast<microseconds>(erapsed_time).count();
                int fps = (int)(1.0F / ((float)(erapsed_ms) / 1000000.0F));
                char c_fps[256];
                wsprintf( c_fps, "FPS : %d", fps );
                SetWindowText( FindWindow("Game_Abyabyabyabyabya ", nullptr), c_fps );
#endif
            }
        }
    }
}

// ダイアログボックスの表示
void PlatformWindows::showDialogBox( const char* Message )
{
    MessageBox(
        window_handle_,
        Message,
        "Error",
        MB_OK | MB_ICONERROR
    );
}
END_EG_EG

//
// ウィンドウプロシージャ実装 
//
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