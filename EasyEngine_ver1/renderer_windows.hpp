///
/// @file   renderer_windows.hpp
/// @author 板場
///
/// @brief  Windows用レンダラー
///
#ifndef INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
#define INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EGEG
class RendererWindows :
    public IRenderer
{
public :
    ///
    /// @brief   コンストラクタ
    ///
    /// @param[in] pDevice : D3Dデバイス
    /// @param[in] pImmediateContext : D3Dデバイスコンテキスト
    /// @param[in] pSwapChain : DXGIスワップチェイン
    ///
    RendererWindows( ID3D11Device* pDevice, 
                     ID3D11DeviceContext* pImmediateContext,
                     IDXGISwapChain* pSwapChain );
    ///
    /// @brief   初期化
    /// @details 生成後に必ず呼び出してください。
    ///
    /// @return  初期化成功[ true ] 初期化失敗[ false ]
    ///
    bool initialize();

// IRenderer
/*-----------------------------------------------------------------*/
    void beginRender( const Vector4D& ) override;
    void entryRender( const Model& ) override;
    void endRender() override;

private :
    ~RendererWindows();

    ID3D11Device*           p_device_;              /// D3D11デバイス
    ID3D11DeviceContext*    p_immediate_context_;   /// D3D11デバイスコンテキスト
    IDXGISwapChain*         p_swap_chain_;          /// DXGIスワップチェイン
    ID3D11RenderTargetView* p_render_target_view_;  /// D3D11レンダーターゲットビュー
    D3D_FEATURE_LEVEL       feature_level_;         /// 採用された機能レベル
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_WINDOWS_HEADER_
/// EOF
