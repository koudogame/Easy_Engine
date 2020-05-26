// �쐬�� : ��
/******************************************************************************

	include

******************************************************************************/
#include "engine.hpp"
#include <tchar.h>
#include "application_status.hpp"


BEGIN_EGEG

/******************************************************************************

    constant

******************************************************************************/
namespace
{
    constexpr DWORD kWindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    constexpr DWORD kWindowStyleEx = WS_EX_OVERLAPPEDWINDOW;
    constexpr RECT  kWindowRegion{ 0L, 0L, kWindowWidth<long>, kWindowHeight<long> };
}


/******************************************************************************

    declaration & definition

******************************************************************************/
 // �R�[���o�b�N�֐��O���錾
LRESULT CALLBACK winProc( HWND, UINT, WPARAM, LPARAM );

 // EasyEngine�����o�ϐ���`
HWND EasyEngine::window_handle_ = 0;
std::unique_ptr<EasyEngine::TaskManagerType> EasyEngine::task_manager_{};
std::unique_ptr<InputDeviceManager> EasyEngine::input_device_manager_{};
std::unique_ptr<RenderingManager> EasyEngine::rendering_manager_{};
std::unique_ptr<LevelManager> EasyEngine::level_manager_{};


/******************************************************************************

	EasyEngine

******************************************************************************/
 // �R���X�g���N�^
EasyEngine::EasyEngine()
{
    
}


 // ������
DetailedReturnValue<bool> EasyEngine::initialize()
{
    auto ret = initializeWindow();
    if( !ret )  return ret;

    ret = initializeManager();
    if( !ret ) return ret;

	return Success{};
}


 // �I������
void EasyEngine::finalize()
{
    level_manager_.reset();
    rendering_manager_.reset();
    input_device_manager_.reset();
    task_manager_.reset();
}


// �E�B���h�E������
DetailedReturnValue<bool> EasyEngine::initializeWindow()
{
    const WNDCLASSEX wndclassex
    {
        sizeof( WNDCLASSEX ),
        CS_VREDRAW,
        winProc,
        0,
        0,
        GetModuleHandle( nullptr ),
        0,
        LoadCursor( nullptr, IDC_ARROW ),
        reinterpret_cast<HBRUSH>( COLOR_WINDOW + 1),
        0,
        _T( "Abyabyabyabyabya" ),
        0
    };
    if( !RegisterClassEx(&wndclassex) ) 
        return { Failure{}, "�E�B���h�E�̓o�^�Ɏ��s���܂����B" };

    RECT region = kWindowRegion;
    if( !AdjustWindowRectEx(&region, kWindowStyle, false, kWindowStyleEx) )
        return { Failure{}, "�E�B���h�E�T�C�Y�̒����Ɏ��s���܂����B" };
    window_handle_ = CreateWindowEx(
        kWindowStyleEx,
        _T( "Abyabyabyabyabya"),
        _T( "EasyEngine" ),
        kWindowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        region.right - region.left,
        region.bottom - region.top,
        nullptr,
        nullptr,
        wndclassex.hInstance,
        nullptr
    );
    if( !window_handle_ ) 
        return { Failure{}, "�E�B���h�E�̐����Ɏ��s���܂����B" };

    ShowWindow( window_handle_, SW_NORMAL );
    return Success{};
}


 // �}�l�[�W���[������
 //
 // note : �������ԂɈˑ��֌W������B
DetailedReturnValue<bool> EasyEngine::initializeManager()
{
    task_manager_ = std::make_unique<TaskManagerType>();

    input_device_manager_ = InputDeviceManager::create();
    if( !input_device_manager_ )
        return { Failure{}, "���̓f�o�C�X�}�l�[�W���[�̐����Ɏ��s���܂����B" };

    rendering_manager_ = RenderingManager::create();
    if( !rendering_manager_ )
        return { Failure{}, "�`��}�l�[�W���[�̐����Ɏ��s���܂����B" };

    level_manager_ = LevelManager::create();
    if( !level_manager_ )
        return { Failure{}, "���x���}�l�[�W���\�̐����Ɏ��s���܂����B" };
    
    return Success{};
}


/******************************************************************************

	others

******************************************************************************/
 // �R�[���o�b�N�֐�
LRESULT CALLBACK winProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
    switch( Message )
    {
    case WM_PAINT :
        {
        PAINTSTRUCT ps;
        BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        }
        return 0;

    case WM_KEYDOWN :
        // Esc�L�[�̓��͂ŏI������
        if( wParam == VK_ESCAPE )
            PostMessage( hWnd, WM_CLOSE, 0, 0 );

    case WM_SYSKEYDOWN :
    case WM_KEYUP :
    case WM_SYSKEYUP :
        EasyEngine::getInputDeviceManager()->eventProcessing( Message, wParam, lParam );
        return 0;

    case WM_DESTROY :
        PostQuitMessage( 0 );
        return 0;

    default :
        return DefWindowProc( hWnd, Message, wParam, lParam );
    }
}

END_EGEG
// EOF
