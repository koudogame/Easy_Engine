// �쐬�� : ��
#include <Windows.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif
#include "application.hpp"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR lpCmdLine,
    int   nCmdShow )
{
#ifdef _DEBUG
    //_CrtSetBreakAlloc(  );
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    const EGEG Application app{};
    app();
}
// EOF
