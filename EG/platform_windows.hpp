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
#include <d3d11.h>
#include "platform.hpp"
#include "renderer.hpp"
#include "shader_loader.hpp"
#include "texture_loader.hpp"
BEGIN_EGEG
class PlatformWindows :
    public IPlatform
{
public :
    static IPlatform* create();

// IPlatform
/*-----------------------------------------------------------------*/
    void gameLoop( std::function<bool(long long)> ) override;
    void showDialogBox( const char * ) override;

    IRenderer* getRenderer() const override { return p_renderer_; }
    IShaderLoader* getShaderLoader() const override { return p_shader_loader_; }
    ITextureLoader* getTextureLoader() const override { return p_texture_loader_; }

private :
    bool initialize();          /// 初期化処理 * 生成時に呼び出す。
    ~PlatformWindows();
    bool initializeWindow();    /// ウィンドウ初期化
    bool initializeDirect3D();  /// Direct3D初期化

    HWND window_handle_;                /// ウィンドウハンドル
    D3D_FEATURE_LEVEL feature_level_;   /// D3D機能レベル
    IRenderer* p_renderer_;             /// レンダラー
    IShaderLoader* p_shader_loader_;    /// シェーダーローダー
    ITextureLoader* p_texture_loader_;  /// テクスチャローダー
};
END_EGEG
#endif /// !INCLUDED_EG_EG_PLATFORM_WINDOWS_HEADER_
/// EOF
