// 作成者 : 板場
#include <Windows.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // !_DEBUG
#include "egeg_math.hpp"
#include "actor2d.hpp"
#include "actor3d.hpp"
#include "unit_factory.hpp"
#include "xinput.hpp"


// エントリーポイント
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR     lpCmdLine,
    INT       nCmdShow )
{
#ifdef  _DEBUG
    //_CrtSetBreakAlloc(  );
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    USING_NS_EGEG;


}
// EOF
