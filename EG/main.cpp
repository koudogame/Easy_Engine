// �쐬�� : ��

#include <Windows.h>
#include "application.hpp"

// �G���g���[�|�C���g
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    easy_engine::Application::instance()->execute();
}
// EOF
