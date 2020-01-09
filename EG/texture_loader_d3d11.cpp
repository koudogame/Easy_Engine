// 作成者 : 板場
#include "texture_loader_d3d11.hpp"
#include "DirectXTex//DirectXTex.h"

#ifdef _DEBUG
#pragma comment( lib, "DirectXTex/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "DirectXTex/Release/DirectXTex.lib" )
#endif

BEGIN_EG_EG
// 関数の実装
/*===========================================================================*/
// テクスチャのロード
bool TextureLoaderD3D11::load( const wchar_t* Path, ITexture** ppOut )
{
    using namespace DirectX;

    auto find = textures_.find( Path );

    // キャッシュにある場合
    if( find != textures_.end() )
    {
        find->second->addRef();
        *ppOut = find->second;
    }
    // 新規に読み込む場合
    else
    {
        // ファイルからデータを読み込む
        TexMetadata mdata;
        ScratchImage image;
        if( FAILED(LoadFromWICFile(Path, 0, &mdata, image)) )
            return false;

        // ビューを作成
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

        TextureD3D11* p_tex = new TextureD3D11( this );
        p_tex->set( view );
        p_tex->addRef();
        *ppOut = p_tex;
    }

    return true;
}
END_EG_EG
// EOF
