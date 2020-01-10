// �쐬�� : ��
#include "platform_windows.hpp"
#include <chrono>
#include "platform_factory.hpp"
#include "renderer_d3d11.hpp"
#include "shader_loader_d3d11.hpp"
#include "texture_loader_d3d11.hpp"

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3d11.lib" )

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );
// �v���b�g�t�H�[���̃t�@�N�g����PlatformWindows��o�^
REGISTER_PLATFORM( EG_EG PlatformID::kWindows, &PlatformWindows::create )

// unnamed namespace
/*===========================================================================*/
namespace
{
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC*, HWND, UINT, UINT );

    constexpr long long kFramePerUS = 16666LL;
    constexpr long kWindowRegionWidth = 1280L;
    constexpr long kWindowRegionHeight = 720L;
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
} // unnamed namespace

BEGIN_EG_EG
// �֐��̎���
/*===========================================================================*/
// ��������
IPlatform* PlatformWindows::create()
{
    PlatformWindows* i = new (std::nothrow) PlatformWindows();
    if( i == nullptr ) return nullptr;
    if( i->initialize() == false )
    {
        i->release();
        return nullptr;
    }

    return i;
}

// ����������
bool PlatformWindows::initialize()
{
    if( initializeWindow() == false )   return false;
    if( initializeDirect3D() == false ) return false;

    return true;
}

// �I������( �f�X�g���N�^ )
PlatformWindows::~PlatformWindows()
{
    p_texture_loader_->release();
    p_shader_loader_->release();
    p_renderer_->release();

    CoUninitialize();
}

// �Q�[�����[�v
void PlatformWindows::gameLoop( std::function<bool(long long)> pFunc )
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;

    MSG msg = {};
    while( msg.message != WM_QUIT )
    {
        // ���b�Z�[�W����
        if( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // �Q�[������
        else
        {
            // �t���[�����[�g����
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

// �_�C�A���O�{�b�N�X�̕\��
void PlatformWindows::showDialogBox( const char* Message )
{
    MessageBox(
        window_handle_,
        Message,
        "Error",
        MB_OK | MB_ICONERROR
    );
}

// �E�B���h�E�̏�����
bool PlatformWindows::initializeWindow()
{
    if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) return false;

    // �E�B���h�E�̓o�^
    WNDCLASSEX wnd = {};
    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.style = CS_VREDRAW;
    wnd.hInstance = GetModuleHandle(nullptr);
    wnd.lpszClassName = "Game_Abyabyabyabyabya";
    wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;
    if (RegisterClassEx(&wnd) == false) return false;


    // �E�B���h�E�̍쐬
    RECT region;
    region.left = region.top = 0L;
    region.right = ::kWindowRegionWidth;
    region.bottom = ::kWindowRegionHeight;
    AdjustWindowRectEx(&region, ::kWindowStyle, false, ::kWindowStyleEx);

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
        nullptr);
    if (window_handle_ == nullptr) return false;

    // �E�B���h�E�̕\��
    ShowWindow(window_handle_, SW_NORMAL);

    return true;
}

// Direct3D�̏�����
bool PlatformWindows::initializeDirect3D()
{
    // �f�o�C�X�ƃX���b�v�`�F�C���̍쐬
    ID3D11Device* p_device;
    ID3D11DeviceContext* p_device_context;
    IDXGISwapChain* p_swap_chain;

    RECT region;
    if( GetClientRect( window_handle_, &region ) == false ) return false;
    DXGI_SWAP_CHAIN_DESC sc_desc = {};
    ::setSwapChainDesc( &sc_desc, window_handle_, region.right, region.bottom );
    if( FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        ::kD3D11CreateFlags,
        ::kD3DFeatureLevels,
        sizeof(::kD3DFeatureLevels) / sizeof(D3D_FEATURE_LEVEL),
        D3D11_SDK_VERSION,
        &sc_desc,
        &p_swap_chain,
        &p_device,
        &feature_level_,
        &p_device_context)) )
        return false;

    // �e��C���^�[�t�F�C�X�̍쐬
    RendererD3D11* p_renderer = new RendererD3D11( p_device, p_device_context, p_swap_chain );
    if( p_renderer->initialize() == false ) 
    {
        p_renderer->release();
        return false;
    }
    p_renderer_ = p_renderer;
    p_shader_loader_ = new ShaderLoaderD3D11( p_device );
    p_texture_loader_ = new TextureLoaderD3D11( p_device );

    // �Ǘ��̕K�v���Ȃ��Ȃ����C���^�[�t�F�C�X���J��
    p_device->Release();
    p_device_context->Release();
    p_swap_chain->Release();

    return true;
}
END_EG_EG

// unnamed namespace
namespace
{
    // �X���b�v�`�F�C���̒�`��ݒ�
    //
    // in pOut   : �ݒ�𔽉f������\���̂̃A�h���X
    // in hWnd   : �`���E�B���h�E�n���h��
    // in Width  : �o�b�N�o�b�t�@��
    // in Height : �o�b�N�o�b�t�@����
    void setSwapChainDesc( DXGI_SWAP_CHAIN_DESC* pOut, HWND hWnd, UINT Width, UINT Height )
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
} // !unnamed namespace

//
// �E�B���h�E�v���V�[�W������ 
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
        // Esc�L�[�̉����ŏI������
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

        return 0;
    case WM_DESTROY :
        PostQuitMessage( 0 );
        return 0;
    }

    // ���̑��̃��b�Z�[�W����
    return DefWindowProc( hWnd, Msg, wParam, lParam );
}
// EOF