// 作成者 : 板場
#include "platform_windows.hpp"
#include <chrono>
#include "platform_factory.hpp"
#include "renderer_windows.hpp"
#include "shader_loader_windows.hpp"
#include "texture_loader_windows.hpp"

#pragma comment( lib, "d3d11.lib" )

// ファクトリに登録
REGISTER_PLATFORM( "Windows", &PlatformWindows::create )

// WindowProcedure
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

namespace
{
    bool createWindow( int, int, HWND* );
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC*, HWND, UINT, UINT );
    HRESULT createD3DDevice( DXGI_SWAP_CHAIN_DESC*, ID3D11Device**, ID3D11DeviceContext**, IDXGISwapChain**, D3D_FEATURE_LEVEL* );

    constexpr long long kFramePerUS = 16666LL;
    constexpr long kWindowRegionWidth = 1280L;
    constexpr long kWindowRegionHeight = 720L;
    constexpr RECT kWindowRegionRect { 0L, 0L, kWindowRegionWidth, kWindowRegionHeight };
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
#ifdef _DEBUG
    constexpr UINT kD3D11CreateFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
    constexpr UINT kD3D11CreateFlags = 0U;
#endif
    constexpr D3D_FEATURE_LEVEL kD3DFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
} // !unnamed namespace

BEGIN_EGEG
// PlatformWindows : 関数の実装
/*===========================================================================*/
// デストラクタ
PlatformWindows::~PlatformWindows()
{
    if( texture_loader_ )   texture_loader_->release();
    if( shader_loader_ )    shader_loader_->release();
    if( renderer_)          renderer_->release();
}

// PlatformWindows生成
IPlatform* PlatformWindows::create()
{
    PlatformWindows* created = new PlatformWindows();
    if( created->initialize() == false )
    {
        created->release();
        return nullptr;
    }

    return created;
}

// メインループ
void PlatformWindows::MainLoop( std::function<bool(long long)> pUpdateFunc )
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

                if( !pUpdateFunc(duration_cast<milliseconds>(erapsed_time).count()) )
                    break;
            }
        }
    }
}

// ダイアログボックスの表示
void PlatformWindows::showDialogBox( const wchar_t* Message )
{
    MessageBox(
        h_window_,
        Message,
        L"Error",
        MB_OK | MB_ICONERROR );
}

// 初期化
// 生成時に呼び出される
//
// return : 成功[ true ] 失敗[ false ]
bool PlatformWindows::initialize()
{
    // プラットフォームの初期化
    RECT region = ::kWindowRegionRect;
    AdjustWindowRectEx( &region, ::kWindowStyle, false, ::kWindowStyleEx );
    long window_width = region.right - region.left;
    long window_height = region.bottom - region.top;
    if( ::createWindow( window_width, window_height, &h_window_ ) == false )
        return false;
    ShowWindow( h_window_, SW_NORMAL );

    DXGI_SWAP_CHAIN_DESC sc_desc = {};
    ::setSwapChainDesc( &sc_desc, h_window_, (UINT)window_width, (UINT)window_height );
    ID3D11Device* p_device;
    ID3D11DeviceContext* p_immediate_context;
    IDXGISwapChain* p_swap_chain;
    if( FAILED(::createD3DDevice( &sc_desc, &p_device, &p_immediate_context, &p_swap_chain, &feature_level_)) )
        return false;

    // レンダラーの生成
    renderer_ = new RendererWindows( p_device, p_immediate_context, p_swap_chain );
    if( static_cast<RendererWindows*>(renderer_)->initialize() == false )
    {
        p_swap_chain->Release();
        p_immediate_context->Release();
        p_device->Release();
        renderer_->release();
        return false;
    }

    // シェーダーローダーの生成
    shader_loader_ = new ShaderLoaderWindows( p_device );

    // テクスチャローダーの生成
    texture_loader_ = new TextureLoaderWindows( p_device );


    // 不要になったインターフェイスを開放
    p_swap_chain->Release();
    p_immediate_context->Release();
    p_device->Release();

    return true;
}
END_EGEG

namespace
{
    // ウィンドウの生成
    //
    // in Width  : ウィンドウの横幅
    // in Height : ウィンドウの高さ
    // out pHWnd : 生成したウィンドウのハンドルを格納する変数のアドレス
    //
    // return true  : 生成志向
    // return false : 生成失敗
    bool createWindow( int Width, int Height, HWND* pHWnd )
    {
        // ウィンドウの登録
        WNDCLASSEX wnd = {};
        wnd.cbSize = sizeof(WNDCLASSEX);
        wnd.style = CS_VREDRAW;
        wnd.hInstance = GetModuleHandle(nullptr);
        wnd.lpszClassName = L"Game_Abyabyabyabyabya";
        wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wnd.lpfnWndProc = WinProc;
        if (RegisterClassEx(&wnd) == false) return false;

        // ウィンドウの生成
        *pHWnd = CreateWindowEx(
            ::kWindowStyleEx,
            wnd.lpszClassName,
            L"EasyEngine",
            ::kWindowStyle,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            Width,
            Height,
            nullptr,
            nullptr,
            wnd.hInstance,
            nullptr);
        if( *pHWnd == nullptr ) return false;

        return true;
    }

    // スワップチェインの定義を設定
    //
    // in pOut   : 設定を反映させる構造体のアドレス
    // in hWnd   : 描画先ウィンドウハンドル
    // in Width  : バックバッファ幅
    // in Height : バックバッファ高さ
    void setSwapChainDesc(DXGI_SWAP_CHAIN_DESC* pOut, HWND hWnd, UINT Width, UINT Height)
    {
        pOut->BufferCount = 1;
        pOut->BufferDesc.Width = Width;
        pOut->BufferDesc.Height = Height;
        pOut->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        pOut->BufferDesc.RefreshRate.Numerator = 60;
        pOut->BufferDesc.RefreshRate.Denominator = 1;
        pOut->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        pOut->OutputWindow = hWnd;
        pOut->SampleDesc.Count = 1;
        pOut->SampleDesc.Quality = 0;
        pOut->Windowed = true;
        pOut->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    }

    // D3Dデバイスとスワップチェインの作成
    //
    // in  pSwapChainDesc  : スワップチェインの設定を格納した構造体のアドレス
    // out ppDevice        : 生成したD3Dデバイスを格納する変数のアドレス
    // out ppDeviceContext : 生成したD3Dデバイスコンテキストを格納する変数のアドレス
    // out ppSwapChain     : 生成したDXGIスワップチェインを格納する変数のアドレス
    // out pFeatureLevel   : 採用されたDirectX機能レベルを格納する変数のアドレス
    //
    // return : D3D11CreateDeviceAndSwapChain関数の戻り値
    HRESULT createD3DDevice( DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, ID3D11Device** ppDevice, ID3D11DeviceContext** ppDeviceContext, IDXGISwapChain** ppSwapChain, D3D_FEATURE_LEVEL* pFeatureLevel )
    {
        return D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            ::kD3D11CreateFlags,
            ::kD3DFeatureLevels,
            sizeof(::kD3DFeatureLevels) / sizeof(D3D_FEATURE_LEVEL),
            D3D11_SDK_VERSION,
            pSwapChainDesc,
            ppSwapChain,
            ppDevice,
            pFeatureLevel,
            ppDeviceContext
        );
    }
} // !unnamed namespace

// WindowProcedure
LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC         hdc;

    switch (Msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);

        return 0;
    case WM_KEYDOWN:
        // Escキーの押下で終了する。
        if (wParam == VK_ESCAPE)
            PostMessage(hWnd, WM_CLOSE, 0, 0);

        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // その他のメッセージ処理
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
// EOF
