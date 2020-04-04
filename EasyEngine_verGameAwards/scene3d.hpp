///
/// @file   scene3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE3D_HEADER_
#define INCLUDED_EGEG_SCENE3D_HEADER_
#include <array>
#include <set>
#include <wrl.h>
#include <d3d11.h>
#include "scene.hpp"
#include "camera.hpp"
#include "actor3d.hpp"
BEGIN_EGEG
///
/// @class  Scene3D
/// @brief  3Dシーン
///
class Scene3D :
    public Scene
{
public :
    ///
    /// @brief  カメラのセット
    ///
    /// @param[in] Camera : カメラ
    ///
    void setCamera( Camera* Camera ) noexcept { camera_ = Camera; }

    ///
    /// @brief  モデルのエントリー
    ///
    /// @param[in] Actor : 描画するアクター
    ///
    void entry( const Actor3D* Actor ) { model_list_.emplace( Actor ); }
    ///
    /// @brief   モデルのエントリー解除
    /// @details entry()関数の呼び出しから、render()関数の呼び出しまでの間に有効です。
    ///
    /// @param[in] Actor : エントリーを解除するモデルを持つアクター
    ///
    void exit( const Actor3D* Actor ) { model_list_.erase( Actor ); }
    
    
/*-----------------------------------------------------------------*/
// Scene
    bool initialize( ID3D11Device* ) override;
    void finalize() override;
    void render( 
        ID3D11DeviceContext* ImmediateContext,
        const std::vector<ID3D11RenderTargetView*>&,
        const std::vector<D3D11_VIEWPORT>&,
        const std::vector<D3D11_RECT>&,
        ID3D11DepthStencilView* = nullptr,
        ID3D11DepthStencilState* = nullptr,
        UINT = 0,
        ID3D11RasterizerState* = nullptr,
        ID3D11BlendState* = nullptr,
        float* = nullptr,
        UINT = 0xFFFFFFFF ) override;
/*-----------------------------------------------------------------*/


protected :
    Camera* camera_ = nullptr;
    std::set<const Actor3D*> model_list_;

    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U> cbuffers_;
};
END_EGEG
#endif /// !INCLUDED_EGEG_SCENE3D_HEADER_
/// EOF
