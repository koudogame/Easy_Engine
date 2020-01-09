///
/// @file    platform_windows.hpp
/// @author  板場
///          
/// @brief   プラットフォーム「Windows」
/// @details 開放を自身のrelease関数のみで行うため<br>
///          デストラクタの呼び出しに制限をかけています。
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
    bool initialize();      /// 初期化処理 * 生成時に呼び出されます。
    ~PlatformWindows();

    unsigned ref_cnt_ = 0;  /// 参照数カウント
    HWND window_handle_;    /// ウィンドウハンドル
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
/// EOF
