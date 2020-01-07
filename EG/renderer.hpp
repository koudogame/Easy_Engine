#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
// 作成者 : 板場
#include "interface.hpp"
#include "vertex_shader.hpp"
#include "pixel_shader.hpp"
#include "texture.hpp"
#include "mesh.hpp"

BEGIN_EG_EG
enum RendererID
{
    kDirect3D11,
};
//
// レンダラーインターフェイス
// RendererFactoryにより生成されることを前提としています。
//
// 初期化が済んでいないインターフェイスの生成を防ぐため、
// インスタンス化を制限しています。
//
class IRenderer :
    public Interface
{
public :
    virtual ~IRenderer() = default;
    
// FileIO
/*-----------------------------------------------------------------*/
    // テクスチャリソースのロード
    virtual bool loadTexture( const wchar_t FilePath[], ITexture** ppOutTexture ) = 0;
    // 頂点シェーダのロード
    virtual bool loadVertexShader( const char FilePath[], IVertexShader** ppOutShader ) = 0;
    // ピクセルシェーダのロード
    virtual bool loadPixelShader( const char FilePath[], IPixelShader** ppOutShader ) = 0;
    
// Render
/*-----------------------------------------------------------------*/
    // レンダー開始
    virtual void beginRender( float BackColorRGBA[4] ) = 0;
    // 頂点シェーダの設定
    virtual void setVertexShader( IVertexShader* pVertexShader ) = 0;
    // ピクセルシェーダの設定
    virtual void setPixelShader( IPixelShader* pPixelShader ) = 0;
    // テクスチャの設定
    virtual void setTexture( ITexture* pTexture ) = 0;
    // メッシュの描画
    virtual void render( const Mesh& Object ) = 0;
    // レンダー終了
    virtual void endRender() = 0;

protected :
    IRenderer() = default;
};
END_EG_EG
#endif //INCLUDED_EG_EG_RENDERER_HEADER_
// EOF
