#ifndef INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
// 作成者 : 板場
#include <Windows.h>
#include "platform.hpp"
#include "renderer.hpp"

BEGIN_EG_EG
//
// プラットフォーム「Windows」
//
// 初期化が必要なので、生成したら必ずinitialize関数で初期化を行って下さい。
//
class PlatformWindows :
    public IPlatform
{
public :
    static IPlatform* create();

    void finalize() override;
    void gameLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const char * ) override;


private :
    bool initialize();

    HWND window_handle_;
};
END_EG_EG
#endif // INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
// EOF
