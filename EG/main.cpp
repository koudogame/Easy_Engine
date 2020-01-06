// 作成者 : 板場
#include <Windows.h>
#include <crtdbg.h>
#include "game.hpp"

// エントリーポイント
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE ,
    LPSTR     lpCmdLine,
    int       nCmdShow )
{
    
#ifdef  _DEBUG
	//メモリリークのチェック
	//_CrtSetBreakAlloc(751);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    using namespace easy_engine;
    Game::instance()->execute();
}

// EOF
