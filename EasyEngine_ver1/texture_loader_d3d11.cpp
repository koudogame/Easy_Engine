// 作成者 : 板場
#include "texture_loader_d3d11.hpp"
#include "DirectXTex/DirectXTex.h"
#include "texture_d3d11.hpp"

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif // !_DEBUG

BEGIN_EGEG
// TextureLoaderD3D11
/*===========================================================================*/
// コンストラクタ
TextureLoaderD3D11::TextureLoaderD3D11( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}

// デストラクタ
TextureLoaderD3D11::~TextureLoaderD3D11()
{
    p_device_->Release();
}

// テクスチャリソースの読み込み
bool TextureLoaderD3D11::load( const std::wstring& Path, ITexture** ppTexture )
{
    using namespace DirectX;

    // ファイルからデータを読み込む
    TexMetadata mdata;
    ScratchImage image;
    if( FAILED(LoadFromWICFile(Path.c_str(), 0, &mdata, image)) )
        return false;

    // シェーダーリソースビューを作成
    ID3D11ShaderResourceView* view;
    if( FAILED(CreateShaderResourceViewEx(
        p_device_,
        image.GetImages(),
        image.GetImageCount(),
        mdata,
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        0,
        false,
        &view)) )
        return false;

    *ppTexture = new TextureD3D11( view );
    view->Release();

    return true;
}
END_EGEG
// EOF
