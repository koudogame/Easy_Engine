// 作成者 : 板場

#include <Windows.h>
#include "application.hpp"

// エントリーポイント
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    easy_engine::Application::instance()->execute();
}
// EOF
