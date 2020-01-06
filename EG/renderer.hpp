#ifndef INCLUDED_EG_EG_RENDERER_HEADER_
#define INCLUDED_EG_EG_RENDERER_HEADER_
// 作成者 : 板場
#include "texture.hpp"
#include "model.hpp"

BEGIN_EG_EG
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
    // 画面のクリア
    virtual void clear( float R, float G, float B, float A ) = 0;
    // モデルの描画
    virtual void render( const Model& Object ) = 0;

protected :
    IRenderer() = default;
};
END_EG_EG
#endif //INCLUDED_EG_EG_RENDERER_HEADER_
// EOF
