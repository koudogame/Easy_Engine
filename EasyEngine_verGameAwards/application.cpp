// 作成者 : 板場
#include "application.hpp"
#include <chrono>
#include <tchar.h>
#include <Windows.h>
#include <wrl.h>
#include <dxgi.h>
#include <d3d11.h>
#include "application_status.hpp"
#include "easy_engine.hpp"

#pragma comment( lib, "dxgi.lib" )

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
    if( EasyEngine::initialize() == false ) return;
    mainloop();
    EasyEngine::finalize();
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
                EasyEngine::getTaskManager()->execute( duration_cast<milliseconds>(erapsed_time).count() );
            }
        }
    }
}

END_EGEG
// EOF
