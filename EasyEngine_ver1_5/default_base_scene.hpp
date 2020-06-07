///
/// @file   default_base_scene.hpp
/// @author 板場
///
#ifndef INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_
#define INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_

#include <array>
#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include "level_scene.hpp"
#include "task.hpp"

BEGIN_EGEG

///
/// @class   DefaultBaseScene
/// @brief   デフォルトベースシーン
///
/// @details デフォルトのベースシーンです。 ウィンドウに書き込みを行います。   <br>
///          説明 <br>
///           このクラスに限らず、ベースシーンはレベルファイルにおいて、他のシーンよりも先に定義する必要があります。 <br>
///           initializeに渡すパラメータはありません。  <br>
///          注意                                   <br>
///           シェーダーに渡す定数バッファについて    <br>
///            頂点シェーダー b0 : 射影変換行列      <br>
///            頂点シェーダー b1 : ビュー変換行列     <br>
///            頂点シェーダー b2 : ワールド変換行列 以上です。
///           
class DefaultBaseScene :
    public LevelScene
{
public :
// override
    bool initialize( std::istream& ) override;
    void finalize() override;
    void entry( RenderComponent* ) override;
    void exit( RenderComponent* ) override;
    void setCamera( LevelCamera* Camera ) override { camera_ = Camera; }
    void addLight( LevelLight* ) override;
    void render( uint64_t ) override;

private :
    bool initializeSceneState();
    void bulidPipeline( ID3D11DeviceContext* );
    bool updateViewMatrix( ID3D11DeviceContext* ) const;
    bool updateWorldMatrix( ID3D11DeviceContext*, LevelNode* ) const;

    Task task_;
    LevelCamera* camera_ = nullptr;
    std::vector<RenderComponent*> models_;
    std::array<Microsoft::WRL::ComPtr<ID3D11Buffer>, 3> cbuffers_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
};

END_EGEG
#endif /// !INCLUDED_EGEG_DEFAULT_BASE_SCENE_HEADER_
/// EOF
