///
/// @file   scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_

#include <array>
#include <vector>
#include <unordered_set>
#include <wrl.h>
#include <d3d11.h>
#include "non_copyable.hpp"

BEGIN_EGEG

class RenderingComponent; ///< RenderingComponent前方宣言( 循環参照回避 )

///
/// @class Scene
/// @brief シーン( レンダリング単位 )
///
class Scene :
    NonCopyable<Scene>
{
public :
    ///
    /// @brief 初期化
    ///
    /// @param[in] Device : D3Dデバイス
    ///
    /// @return true:成功　false:失敗
    ///
    bool initialize( ID3D11Device* Device );

    ///
    /// @brief 終了
    ///
    void finalize();

    ///
    /// @brief カメラをセット
    ///
    /// @param[in] Camera : カメラ
    ///
    void setCamera( const void* Camera ) noexcept { /*camera_ = Camera;*/ }

    ///
    /// @brief シーンステートの設定
    ///
    /// @param[in] RenderTargetViews : 描画ターゲットリスト
    /// @param[in] Viewports         : ビューポートリスト
    /// @param[in] ScissorRects      : シザー矩形リスト
    /// @param[in] DepthStencilView  : 深度ステンシルビュー
    /// @param[in] DepthStencilState : 深度ステンシルステート
    /// @param[in] StencilReference  : ステンシルテスト用参照値
    /// @param[in] RasterizerState   : ラスタライザステート
    /// @param[in] BlendState        : ブレンドステート
    /// @param[in] BlendFactor       : D3D11_BLEND_BLEND_FACTOR使用時に使用する定数値
    /// @param[in] BlendMask         : マルチサンプル用マスク
    ///
    /// @details コンテナを使用した引数について、効率よく扱うため値渡しになっています。<br>
    ///           恩恵を受けるためにはにはstd::move(...)を使用して下さい
    ///
    void setState(
        std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> RenderTargetViews,
        std::vector<D3D11_VIEWPORT> Viewports,
        std::vector<D3D11_RECT> ScissorRects,
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& DepthStencilView = {},
        const Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& DepthStencilState = {},
        UINT StencilReference = 0,
        const Microsoft::WRL::ComPtr<ID3D11RasterizerState>& RasterizerState = {},
        const Microsoft::WRL::ComPtr<ID3D11BlendState>& BlendState = {},
        const std::array<float, 4>& BlendFactor = { 0.0F, 0.0F, 0.0F, 0.0F},
        UINT BlendMask = 0xFFFFFFFF ) noexcept;

    ///
    /// @brief  シーンのクリア
    ///
    /// @param[in] DC    : デバイスコンテキスト
    /// @param[in] Color : クリア色
    ///
    void clear( ID3D11DeviceContext* DC, const std::array<float, 4>& Color = {1.0F, 1.0F, 1.0F, 1.0F} );
    ///
    /// @brief シーンの描画
    ///
    /// @param[in] DC : デバイスコンテキスト
    ///
    void render( ID3D11DeviceContext* DC );

    ///
    /// @brief 描画オブジェクトを追加
    ///
    /// @param[in] Component : 追加対象
    ///
    void entry( const RenderingComponent* Component ) { models_.emplace( Component ); }
    ///
    /// @brief 描画オブジェクトを削除
    ///
    /// @param[in] Component : 削除対象
    ///
    void exit( const RenderingComponent* Component ) noexcept { models_.erase( Component ); }

private :
    std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>> render_target_views_;
    std::vector<D3D11_VIEWPORT> viewports_;
    std::vector<D3D11_RECT>     scissor_rects_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    UINT stencil_reference_ = 0;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    std::array<float, 4U> blend_factor_;
    UINT blend_mask_ = 0;
    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U> cbuffers_;
    const void* camera_ = nullptr;
    std::unordered_set<const RenderingComponent*> models_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
