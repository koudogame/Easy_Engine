// �쐬�� : ��
#include "platform_windows.hpp"
#include <chrono>
#include "platform_factory.hpp"
#include "renderer_windows.hpp"
#include "shader_loader_windows.hpp"
#include "texture_loader_windows.hpp"

#pragma comment( lib, "d3d11.lib" )

// �t�@�N�g���ɓo�^
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
// PlatformWindows : �֐��̎���
/*===========================================================================*/
// �f�X�g���N�^
PlatformWindows::~PlatformWindows()
{
    if( texture_loader_ )   texture_loader_->release();
    if( shader_loader_ )    shader_loader_->release();
    if( renderer_)          renderer_->release();
}

// PlatformWindows����
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

// ���C�����[�v
void PlatformWindows::MainLoop( std::function<bool(long long)> pUpdateFunc )
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

                if( !pUpdateFunc(duration_cast<milliseconds>(erapsed_time).count()) )
                    break;
            }
        }
    }
}

// �_�C�A���O�{�b�N�X�̕\��
void PlatformWindows::showDialogBox( const wchar_t* Message )
{
    MessageBox(
        h_window_,
        Message,
        L"Error",
        MB_OK | MB_ICONERROR );
}

// ������
// �������ɌĂяo�����
//
// return : ����[ true ] ���s[ false ]
bool PlatformWindows::initialize()
{
    // �v���b�g�t�H�[���̏�����
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

    // �����_���[�̐���
    renderer_ = new RendererWindows( p_device, p_immediate_context, p_swap_chain );
    if( static_cast<RendererWindows*>(renderer_)->initialize() == false )
    {
        p_swap_chain->Release();
        p_immediate_context->Release();
        p_device->Release();
        renderer_->release();
        return false;
    }

    // �V�F�[�_�[���[�_�[�̐���
    shader_loader_ = new ShaderLoaderWindows( p_device );

    // �e�N�X�`�����[�_�[�̐���
    texture_loader_ = new TextureLoaderWindows( p_device );


    // �s�v�ɂȂ����C���^�[�t�F�C�X���J��
    p_swap_chain->Release();
    p_immediate_context->Release();
    p_device->Release();

    return true;
}
END_EGEG

namespace
{
    // �E�B���h�E�̐���
    //
    // in Width  : �E�B���h�E�̉���
    // in Height : �E�B���h�E�̍���
    // out pHWnd : ���������E�B���h�E�̃n���h�����i�[����ϐ��̃A�h���X
    //
    // return true  : �����u��
    // return false : �������s
    bool createWindow( int Width, int Height, HWND* pHWnd )
    {
        // �E�B���h�E�̓o�^
        WNDCLASSEX wnd = {};
        wnd.cbSize = sizeof(WNDCLASSEX);
        wnd.style = CS_VREDRAW;
        wnd.hInstance = GetModuleHandle(nullptr);
        wnd.lpszClassName = L"Game_Abyabyabyabyabya";
        wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wnd.lpfnWndProc = WinProc;
        if (RegisterClassEx(&wnd) == false) return false;

        // �E�B���h�E�̐���
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

    // �X���b�v�`�F�C���̒�`��ݒ�
    //
    // in pOut   : �ݒ�𔽉f������\���̂̃A�h���X
    // in hWnd   : �`���E�B���h�E�n���h��
    // in Width  : �o�b�N�o�b�t�@��
    // in Height : �o�b�N�o�b�t�@����
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

    // D3D�f�o�C�X�ƃX���b�v�`�F�C���̍쐬
    //
    // in  pSwapChainDesc  : �X���b�v�`�F�C���̐ݒ���i�[�����\���̂̃A�h���X
    // out ppDevice        : ��������D3D�f�o�C�X���i�[����ϐ��̃A�h���X
    // out ppDeviceContext : ��������D3D�f�o�C�X�R���e�L�X�g���i�[����ϐ��̃A�h���X
    // out ppSwapChain     : ��������DXGI�X���b�v�`�F�C�����i�[����ϐ��̃A�h���X
    // out pFeatureLevel   : �̗p���ꂽDirectX�@�\���x�����i�[����ϐ��̃A�h���X
    //
    // return : D3D11CreateDeviceAndSwapChain�֐��̖߂�l
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
        // Esc�L�[�̉����ŏI������B
        if (wParam == VK_ESCAPE)
            PostMessage(hWnd, WM_CLOSE, 0, 0);

        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // ���̑��̃��b�Z�[�W����
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
// EOF
