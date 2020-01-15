// 作成者 : 板場
#include "texture_loader_windows.hpp"
#include "DirectXTex/DirectXTex.h"
#include "texture_windows.hpp"

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif // !_DEBUG

BEGIN_EGEG
// TextureLoaderWindows : 関数の実装
/*===========================================================================*/
// コンストラクタ
TextureLoaderWindows::TextureLoaderWindows( ID3D11Device* pDevice ) :
    p_device_( pDevice )
{
    p_device_->AddRef();
}

// デストラクタ
TextureLoaderWindows::~TextureLoaderWindows()
{
    p_device_->Release();
}

// テクスチャリソースの読み込み
bool TextureLoaderWindows::load( const wchar_t* Path, ITexture** ppTexture )
{
    using namespace DirectX;

    // ファイルからデータを読み込む
    TexMetadata mdata;
    ScratchImage image;
    if( FAILED(LoadFromWICFile(Path, 0, &mdata, image)) )
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

    *ppTexture = new TextureWindows( view );
    view->Release();

    return true;
}
END_EGEG
// EOF
