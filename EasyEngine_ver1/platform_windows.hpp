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
    void showDialogBox( const wchar_t* ) override;
    IRenderer* getRenderer() const override { return renderer_; }
    IShaderLoader* getShaderLoader() const override { return shader_loader_; }
    ITextureLoader* getTextureLoader() const override { return texture_loader_; }

private :
    ~PlatformWindows();
    bool initialize();

    HWND h_window_;                             /// ウィンドウハンドル
    D3D_FEATURE_LEVEL feature_level_;           /// 採用されたDirectX機能レベル
    IRenderer* renderer_ = nullptr;             /// レンダラー
    IShaderLoader* shader_loader_ = nullptr;    /// シェーダーローダー
    ITextureLoader* texture_loader_ = nullptr;  /// テクスチャローダー
};
END_EGEG
#endif /// !INCLUDED_EGEG_PLATFORM_WINDOWS_HEADER_
/// EOF
