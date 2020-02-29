// 作成者 : 板場
#include "application.hpp"
#include <chrono>
#include <tchar.h>
#include <Windows.h>
#include "application_status.hpp"
#include "xinput_controller.hpp"


// ウィンドウプロシージャ関数宣言
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEX = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace


BEGIN_EGEG
// Application 関数定義
/*===========================================================================*/
// 実行
void Application::run()
{
    if( initialize() == false ) return;
    mainloop();
    finalize();
}

// 初期化
bool Application::initialize()
{
    // ウィンドウ登録
    WNDCLASSEX wnd = {};
    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.style = CS_VREDRAW;
    wnd.hInstance = GetModuleHandle(nullptr);
    wnd.lpszClassName = _T("Game_Abyabyabyabyabya");
    wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;
    if (RegisterClassEx(&wnd) == false) return false;

    // クライアント領域が解像度に合うよう、ウィンドウサイズを調整
    RECT region;
    region.left = region.top = 0L;
    region.right = getHorizontalResolution<long>();
    region.bottom = getVerticalResolution<long>();
    if( AdjustWindowRectEx(&region, ::kWindowStyle, false, ::kWindowStyleEX) == false )
        return false;

    // ウィンドウ作成
    HWND h_wnd = CreateWindowEx(
        ::kWindowStyleEX,
        wnd.lpszClassName,
        _T("EasyEngine"),
        ::kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        nullptr,
        nullptr,
        wnd.hInstance,
        nullptr);
    if( h_wnd == nullptr ) return false;

    // ウィンドウ表示
    ShowWindow(h_wnd, SW_NORMAL);

    return true;
}

// 終了
void Application::finalize()
{

}

// メインループ
void Application::mainloop()
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;

    MSG msg{};
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
            if( duration_cast<microseconds>(erapsed_time).count() >= TimePerFrame<>::value )
            {
                last_time = curr_time;
            }
        }
    }
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
        // Escキーの押下で終了する。
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, Message, wParam, lParam );
}
// EOF
