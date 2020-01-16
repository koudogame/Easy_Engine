///
/// @file   platform_windows.hpp
/// @author 板場
///
/// @brief  プラットフォーム「Windows」
///
#ifndef INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
#define INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
#include <Windows.h>
#include <d3d11.h>
#include "platform.hpp"
BEGIN_EGEG
class PlatformWindows :
    public IPlatform
{
public :
    ///
    /// @brief   PlatformWindowsの生成処理
    /// @details PlatformFactoryに登録する関数です。
    ///
    /// @return  new PlatformWindows
    ///
    static IPlatform* create();

// IPlatform
/*-----------------------------------------------------------------*/
    void MainLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const std::string& ) override;
    bool createRenderer( IRenderer** ) override;
    bool createShaderLoader( IShaderLoader** ) override;
    bool createTextureLoader( ITextureLoader** ) override;

private :
    ~PlatformWindows();
    bool initialize();

    HWND h_window_;                             /// ウィンドウハンドル
    D3D_FEATURE_LEVEL feature_level_;           /// 採用されたDirectX機能レベル
    ID3D11Device* p_device_;                    /// D3Dデバイス
    ID3D11DeviceContext* p_immediate_context_;  /// D3Dデバイスコンテキスト
    IDXGISwapChain* p_swap_chain_;              /// DXGIスワップチェイン
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
/// EOF
