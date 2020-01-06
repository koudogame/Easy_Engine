#ifndef INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
// �쐬�� : ��
#include <Windows.h>
#include "platform.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// �v���b�g�t�H�[���uWindows�v
//
// ���������K�v�Ȃ̂ŁA����������K��initialize�֐��ŏ��������s���ĉ������B
//
class PlatformWindows :
    public IPlatform
{
public :
    static IPlatform* create();

    void addRef() override { ++ref_cnt_; }
    void release() override;

    void gameLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const char * ) override;

    bool initialize();
    void finalize();

private :
    unsigned ref_cnt_ = 0;
    HWND window_handle_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
// EOF
