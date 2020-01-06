#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
// 作成者 : 板場
#include "texture.hpp"
#include "model.hpp"

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
class IRenderer
{
public :
    virtual ~IRenderer() = default;

    virtual bool initialize() = 0;
    virtual void finalize() = 0;
    
// FileIO
/*-----------------------------------------------------------------*/
    // テクスチャリソースのロード
    //virtual bool loadResource( const wchar_t FilePath[], ITexture* pOut ) = 0;

    //// シェーダのロード
    //virtual bool loadVertexShader( const char FilePath[], IShader* pOut ) = 0;
    //virtual bool loadPixelShader( const char FilePath[], IShader* pOut ) = 0;
    //// シェーダのアンロード
    //virtual void unloadShader( IShader* pOut ) = 0;
    
// Render
/*-----------------------------------------------------------------*/
    // レンダー開始
    virtual void beginRender( float BackColorRGBA[4] ) = 0;
    // モデルの描画
    virtual void render( const Model& Object ) = 0;
    // レンダー終了
    virtual void endRender() = 0;

protected :
    IRenderer() = default;
};
END_EG_EG
#endif //INCLUDED_EG_EG_RENDERER_HEADER_
// EOF
