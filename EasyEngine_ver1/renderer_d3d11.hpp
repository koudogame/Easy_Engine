///
/// @file   renderer_d3d11.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_RENDERER_D3D11_HEADER_
#define INCLUDED_EGEG_RENDERER_D3D11_HEADER_
#include <deque>
#include <d3d11.h>
#include "renderer.hpp"
BEGIN_EGEG
///
/// @class  RendererD3D11
///
/// @brief  DirectX11用レンダラー
///
class RendererD3D11 :
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
    RendererD3D11( ID3D11Device* pDevice, 
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
    Vector2D getScreenSize() const override { return {viewport_.Width, viewport_.Height}; }
    void clear( const Vector4D& ) override;
    void beginRender() override;
    void renderModel( const Model&, BlendMode ) override;
    void endRender() override;

private :
    ~RendererD3D11();

    ID3D11Device*           p_device_;              /// D3D11デバイス
    ID3D11DeviceContext*    p_immediate_context_;   /// D3D11デバイスコンテキスト
    IDXGISwapChain*         p_swap_chain_;          /// DXGIスワップチェイン
    ID3D11RenderTargetView* p_render_target_view_;  /// D3D11レンダーターゲットビュー
    D3D_FEATURE_LEVEL       feature_level_;         /// 採用された機能レベル
    D3D11_VIEWPORT          viewport_;              /// ビューポート
    ID3D11SamplerState*     p_sampler_state_;       /// サンプラーステート
    ID3D11BlendState*       p_blend_states_[3];     /// ブレンドステート配列
    std::deque<Model>       model_list_;            /// 描画バッチ
};
END_EGEG
#endif /// !INCLUDED_EGEG_RENDERER_D3D11_HEADER_
/// EOF
