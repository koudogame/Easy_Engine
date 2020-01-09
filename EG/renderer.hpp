///
/// @file    renderer.hpp
/// @author  板場
///          
/// @brief   レンダラーインターフェイス
/// @details RendererFactoryにより提供されます。<br>
///          新しいレンダラーを作成する際、RendererFactoryへの登録を必ず行って下さい。<br>
///          登録の際はIDも一緒に登録するため、RendererIDに識別IDを追加して下さい。
///
#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
#include "interface.hpp"
#include "pixel_shader.hpp"
#include "vertex_shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"
BEGIN_EG_EG
///
/// @enum  RendererID
/// @brief レンダラーを識別するID群です。
///
enum RendererID
{
    kDirect3D11,
};

class IRenderer :
    public Interface
{
public :
    ///
    /// @brief  レンダー開始
    ///
    /// @param[in] ClearColorRGBA : クリア色 { R, G, B, A }
    ///
    virtual void beginRender( float ClearColorRGBA[4] ) = 0;
    ///
    /// @brief  グラフィックスパイプラインに頂点シェーダを設定
    ///
    /// @param[in] pVertexShader : 設定する頂点シェーダ
    ///
    virtual void setVertexShader( IVertexShader* pVertexShader ) = 0;
    ///
    /// @brief  グラフィックスパイプラインにピクセルシェーダを設定
    ///
    /// @param[in] pPixelShader : 設定するピクセルシェーダ
    ///
    virtual void setPixelShader( IPixelShader* pPixelShader ) = 0;
    ///
    /// @brief  グラフィックスパイプラインにテクスチャを設定
    ///
    /// @param[in] pTexture : 設定するテクスチャ
    ///
    virtual void setTexture( ITexture* pTexture ) = 0;
    ///
    /// @brief  メッシュのレンダリング
    ///
    /// @param[in]  Object : レンダリングするメッシュデータ
    ///
    virtual void render( const Mesh& Object ) = 0;
    ///
    /// @brief  レンダー終了
    ///
    virtual void endRender() = 0;

protected :
    IRenderer() = default;
    virtual ~IRenderer() = default;
};
END_EG_EG
#endif /// !INCLUDED_EG_EG_RENDERER_HEADER_
/// EOF
