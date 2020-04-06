// �쐬�� : ��
#include "easy_engine.hpp"
#include <Windows.h>
#include <tchar.h>
#include "application_status.hpp"
#include "keyboard.hpp"
#include "task.hpp"

// �E�B���h�E�v���V�[�W���֐��錾
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

BEGIN_EGEG

// �N���X��`
/*===========================================================================*/
struct EasyEngine::Impl
{
    HWND h_wnd_;
    std::shared_ptr<RenderingManager> rendering_manager_;
    JobScheduler<Task> task_manager;

    bool createWindow();
};


// �萔��`
/*===========================================================================*/
namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEX = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace


// ���̂̐錾
/*===========================================================================*/
std::unique_ptr<EasyEngine::Impl> EasyEngine::p_impl_;


// EasyEngine �֐���`
/*===========================================================================*/
// �G���W��������
DetailedReturnValue<bool> EasyEngine::initialize()
{
    using RetTy = DetailedReturnValue<bool>;

    // �G���W���̎������𐶐�
    try {
        p_impl_ = std::make_unique<Impl>();
    }
    catch ( const std::bad_alloc& e ) {
        return RetTy( false, e.what() );
    }

    // �E�B���h�E�̐������\��
    if( p_impl_->createWindow() == false )
        return RetTy( false, "�E�B���h�E�̐����Ɏ��s" );
    ShowWindow( p_impl_->h_wnd_, SW_NORMAL );

    // �����_�����O�G���W����ݒ�
    try {
        p_impl_->rendering_manager_ = RenderingManager::create();
    } catch( const std::runtime_error& e ) {
        return RetTy( false, e.what() );
    } catch( const std::bad_alloc& e ) {
        return RetTy( false, e.what() );
    }


    return true;
};

// �G���W���I��
void EasyEngine::finalize()
{
    p_impl_.reset( nullptr );
}

// �E�B���h�E�n���h���̎擾
HWND EasyEngine::getWindowHandle() noexcept
{
    return p_impl_->h_wnd_;
}

// �����_�����O�G���W���̎擾
std::shared_ptr<RenderingManager> EasyEngine::getRenderingManager() noexcept
{
    return p_impl_->rendering_manager_;
}

// �^�X�N�}�l�[�W���\�̎擾
JobScheduler<Task>* EasyEngine::getTaskManager() noexcept
{
    return &p_impl_->task_manager;
}

// EasyEngine::Impl �֐���`
/*===========================================================================*/
// �E�B���h�E�̍쐬
class WindowRegisterer
{
public :
    WindowRegisterer( const WNDCLASSEX& Wnd)
    {
        if (RegisterClassEx(&Wnd) == false) throw std::runtime_error( "�E�B���h�E�̓o�^���s�B" );
    }
};
bool EasyEngine::Impl::createWindow()
{
    // �E�B���h�E��o�^( ��x�̂ݎ��s )
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

    // �N���C�A���g�̈悪�𑜓x�ɍ����悤�A�E�B���h�E�T�C�Y�𒲐�
    RECT region;
    region.left = region.top = 0L;
    region.right = kHorizontalResolution<long>;
    region.bottom = kVerticalResolution<long>;
    if( AdjustWindowRectEx(&region, kWindowStyle, false, kWindowStyleEX) == false )
        return false;

    // �E�B���h�E�쐬
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

// WinProc �֐���`
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
        // Esc�L�[�̉����ŏI������B
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

    case WM_KEYUP :
    case WM_SYSKEYUP :
        EGEG Keyboard::instance()->eventProcessing( Message, wParam, lParam );
        return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, Message, wParam, lParam );
}

// EOF
