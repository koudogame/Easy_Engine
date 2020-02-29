// �쐬�� : ��
#include "application.hpp"
#include <chrono>
#include <tchar.h>
#include <Windows.h>
#include "application_status.hpp"
#include "xinput_controller.hpp"


// �E�B���h�E�v���V�[�W���֐��錾
LRESULT CALLBACK WinProc( HWND, UINT, WPARAM, LPARAM );

namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEX = WS_EX_OVERLAPPEDWINDOW;
} // unnamed namespace


BEGIN_EGEG
// Application �֐���`
/*===========================================================================*/
// ���s
void Application::run()
{
    if( initialize() == false ) return;
    mainloop();
    finalize();
}

// ������
bool Application::initialize()
{
    // �E�B���h�E�o�^
    WNDCLASSEX wnd = {};
    wnd.cbSize = sizeof(WNDCLASSEX);
    wnd.style = CS_VREDRAW;
    wnd.hInstance = GetModuleHandle(nullptr);
    wnd.lpszClassName = _T("Game_Abyabyabyabyabya");
    wnd.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;
    if (RegisterClassEx(&wnd) == false) return false;

    // �N���C�A���g�̈悪�𑜓x�ɍ����悤�A�E�B���h�E�T�C�Y�𒲐�
    RECT region;
    region.left = region.top = 0L;
    region.right = getHorizontalResolution<long>();
    region.bottom = getVerticalResolution<long>();
    if( AdjustWindowRectEx(&region, ::kWindowStyle, false, ::kWindowStyleEX) == false )
        return false;

    // �E�B���h�E�쐬
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

    // �E�B���h�E�\��
    ShowWindow(h_wnd, SW_NORMAL);

    return true;
}

// �I��
void Application::finalize()
{

}

// ���C�����[�v
void Application::mainloop()
{
    using namespace std::chrono;

    time_point<high_resolution_clock> last_time = high_resolution_clock::now();
    time_point<high_resolution_clock> curr_time;

    MSG msg{};
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
            if( duration_cast<microseconds>(erapsed_time).count() >= TimePerFrame<>::value )
            {
                last_time = curr_time;
            }
        }
    }
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
        // Esc�L�[�̉����ŏI������B
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
