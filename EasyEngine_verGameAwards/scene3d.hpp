///
/// @file   scene3d.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_SCENE3D_HEADER_
#define INCLUDED_EGEG_SCENE3D_HEADER_

#include <array>
#include <set>
#include "scene.hpp"
#include "camera3d.hpp"
#include "actor3d.hpp"

BEGIN_EGEG

///
/// @class   Scene3D
/// @brief   3Dシーン
/// @details prepare関数では、配置されているモデルをクリアします。                                               <br>
///          モデルのエントリーは、prepare呼び出しから、render呼び出しの間に行って下さい。                       <br>
///          同一のシーンを複数回描画したい場合等は、                                                            <br>
///          一度のprepare関数呼び出しに対して複数のrender関数を呼び出して下さい。                               <br>
///          ループを跨いでのrender関数呼び出しも可能ですが、予期せぬ不具合を招く可能性があるので避けてください。<br>
///          このシーンがシェーダーにセットする定数バッファは、                                                  <br>
///          「頂点シェーダ―」                                                                                  <br>
///             b0 : 射影変換行列
///             b1 : ビュー変換行列
///             b2 : ワールド変換行列                                                                            <br>
///          です。
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
    void setCamera( const Camera3D* Camera ) noexcept { camera_ = Camera; }

    ///
    /// @brief  アクターのエントリー
    ///
    /// @param[in] Actor : 描画するアクター
    ///
    void entry( const Actor3D* Actor ) { actor_list_.emplace( Actor ); }
    ///
    /// @brief   アクターのエントリー解除
    ///
    /// @param[in] Actor : エントリーを解除するアクター
    ///
    void exit( const Actor3D* Actor ) { actor_list_.erase( Actor ); }
    
    
/*-----------------------------------------------------------------*/
// Scene
    bool initialize( RenderingManager* ) override;
    void finalize() override;
    void prepare() override;
    void render( 
        ID3D11DeviceContext*,
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

private :
    const Camera3D* camera_ = nullptr;
    std::set<const Actor3D*> actor_list_;

    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3U> cbuffers_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_SCENE3D_HEADER_
/// EOF
