// �쐬�� : ��

#include "application.hpp"
#include <Windows.h>
#include "game.hpp"


// �E�B���h�E�v���V�[�W��
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

// �����N���X�̒�`
/*===========================================================================*/
class Application::Impl
{
public:
    bool initialize();
    void finalize();

    HWND h_window_;
};


// �֐��̎���
/*===========================================================================*/
// Ctor
Application::Application() :
    p_impl_( std::make_unique<Impl>() )
{
}

// �C���X�^���X�̕ԋp( pimpl�C�f�B�I�����g�p���Ă��邽�߁A�C�����C�����ł��Ȃ� )
Application* Application::instance()
{
    static Application i;
    return &i;
}

// ���s����
void Application::execute()
{
    // �A�v���P�[�V�����̏�����
    if( p_impl_->initialize() == false ) return;

    // �Q�[���̎��s
    Game game;
    game.execute();

    // �A�v���P�[�V�����̏I��
    p_impl_->finalize();
}

// �A�v���P�[�V��������������
//
// �A�v���P�[�V�����̏������ɕK�v�ȏ��������s����B
//
// �������ɐ��������ꍇ�@true
// �������Ɏ��s�����ꍇ�@false ��߂�l�Ƃ��ĕԋp����B
bool Application::Impl::initialize()
{
    // �E�B���h�E�̓o�^
    WNDCLASSEX wnd = {};
    wnd.cbSize        = sizeof( WNDCLASSEX );
    wnd.style         = CS_VREDRAW;
    wnd.hInstance     = GetModuleHandle( nullptr );
    wnd.lpszClassName = "Game_MainWindow";
    wnd.hCursor       = LoadCursor( nullptr, IDC_ARROW );
    wnd.hbrBackground = reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1 );
    wnd.lpfnWndProc   = WinProc;
    if( RegisterClassEx( &wnd ) == false ) return false;

    // �E�B���h�E�̍쐬
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

// �A�v���P�[�V�����I������
//
// �K�v�ɉ����ĊJ���������s��
void Application::Impl::finalize()
{

}

END_EG_EG

// �E�B���h�E�v���V�[�W������
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
