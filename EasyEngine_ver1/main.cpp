// 作成者 : 板場
#include <Windows.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG
#include "easy_engine.hpp"

// エントリーポイント
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR     lpCmdLine,
    INT       nCmdShow)
{
#ifdef  _DEBUG
    //_CrtSetBreakAlloc(  );
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    EGEG EasyEngine engine;
    engine.run( "Windows" );
}
// EOF
