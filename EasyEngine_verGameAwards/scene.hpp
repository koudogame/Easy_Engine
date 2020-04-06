///
/// @file   scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE_HEADER_
#define INCLUDED_EGEG_SCENE_HEADER_
#include <type_traits>
#include <wrl.h>
#include <d3d11.h>
#include "noncopyable.hpp"
#include "easy_engine.hpp"
BEGIN_EGEG
///
/// @class   Scene
/// @brief   レンダリング単位
///
class Scene :
    NonCopyable<Scene>
{
public :
    virtual ~Scene() = default;

    ///< 初期化処理
    virtual bool initialize( ID3D11Device* Device ) = 0;

    ///< 終了処理
    virtual void finalize() = 0;

    ///
    /// @brief  描画準備
    ///
    virtual void prepare() = 0;

    ///
    /// @brief  描画
    ///
    /// @param[in] ImmediateContext  : デバイスコンテキスト
    /// @param[in] RenderTargetView  : 描画ターゲットビュー
    /// @param[in] Viewports         : ビューポート
    /// @param[in] ScissorRects:     : シザー矩形
    /// @param[in] DepthStencilView  : 深度ステンシルビュー
    /// @param[in] DepthStencilState : 深度ステンシルステート
    /// @param[in] StencilRef        : ステンシルテストで使用する参照値
    /// @param[in] RasterizerState   : ラスタライザステート
    /// @param[in] BlendState        : ブレンドステート
    /// @param[in] BlendFactor       : ブレンドステート定数
    /// @param[in] BlendMask         : ブレンドステートサンプル用マスク
    ///
    virtual void render(
        ID3D11DeviceContext* ImmediateContext,
        const std::vector<ID3D11RenderTargetView*>& RenderTargetViews,
        const std::vector<D3D11_VIEWPORT>& Viewports,
        const std::vector<D3D11_RECT>& ScissorRects,
        ID3D11DepthStencilView* DepthStencilView = nullptr,
        ID3D11DepthStencilState* DepthStencilState = nullptr,
        UINT StencilRef = 0,
        ID3D11RasterizerState* RasterizerState = nullptr,
        ID3D11BlendState* BlendState = nullptr,
        float* BlendFactor = nullptr,
        UINT BlendMask = 0xFFFFFFFF ) = 0;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE_HEADER_
/// EOF
