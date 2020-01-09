///
/// @file    platform_windows.hpp
/// @author  ��
///          
/// @brief   �v���b�g�t�H�[���uWindows�v
/// @details �J�������g��release�֐��݂̂ōs������<br>
///          �f�X�g���N�^�̌Ăяo���ɐ����������Ă��܂��B
///
#ifndef INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#include <Windows.h>
#include "platform.hpp"
#include "renderer.hpp"
BEGIN_EG_EG
class PlatformWindows :
    public IPlatform
{
public :
    static IPlatform* create();

// Interface override
/*-----------------------------------------------------------------*/
    void addRef() override { ++ref_cnt_; }
    void release() override;

// IPlatform override
/*-----------------------------------------------------------------*/
    void gameLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const char * ) override;

private :
    bool initialize();      /// ���������� * �������ɌĂяo����܂��B
    ~PlatformWindows();

    unsigned ref_cnt_ = 0;  /// �Q�Ɛ��J�E���g
    HWND window_handle_;    /// �E�B���h�E�n���h��
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
/// EOF
