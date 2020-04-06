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

#include "test_level.hpp"
#include "keyboard_controller.hpp"
#include "task.hpp"
#include "input_device_manager.hpp"


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
template <class Ty>
using ComPtr = Microsoft::WRL::ComPtr<Ty>;
void Application::mainloop()
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;
   
    ComPtr<IDXGIFactory> factory;
    HRESULT hr = CreateDXGIFactory( IID_PPV_ARGS(&factory) );
    if( FAILED(hr) )    return;

    ComPtr<IDXGISwapChain> sc;
    DXGI_SWAP_CHAIN_DESC sc_desc {};
        sc_desc.BufferCount = 1;
        sc_desc.BufferDesc.Width = kHorizontalResolution<UINT>;
        sc_desc.BufferDesc.Height = kVerticalResolution<UINT>;
        sc_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sc_desc.BufferDesc.RefreshRate.Numerator = 60;
        sc_desc.BufferDesc.RefreshRate.Denominator = 1;
        sc_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sc_desc.OutputWindow = EasyEngine::getWindowHandle();
        sc_desc.SampleDesc.Count = 1;
        sc_desc.SampleDesc.Quality = 0;
        sc_desc.Windowed = true;
        sc_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    hr = factory->CreateSwapChain(
        EasyEngine::getRenderingManager()->getDevice().Get(),
        &sc_desc,
        &sc
    );
    if( FAILED(hr) ) _asm int 3;
    ComPtr<ID3D11Texture2D> back_buffer = nullptr;
    hr = sc->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&back_buffer
    );
    if( FAILED(hr) ) _asm int 3;
    ComPtr<ID3D11RenderTargetView> render_target;
    EasyEngine::getRenderingManager()->getDevice()->
    CreateRenderTargetView(
        back_buffer.Get(),
        nullptr,
        &render_target
    );

    TestLevel level;
    if( !level.initialize() )    return;


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

                float backcolor[4] = { 1.0F, 1.0F, 1.0F, 1.0F };
                EasyEngine::getRenderingManager()->getImmediateContext()->
                ClearRenderTargetView(
                    render_target.Get(),
                    backcolor
                );

                level.update( render_target.Get() );
                
                sc->Present(0,0);
            }
        }
    }

    level.finalize();
}

END_EGEG
// EOF
