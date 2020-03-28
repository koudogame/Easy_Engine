// 作成者 : 板場
#include "texture_loader.hpp"
#include "lib/DirectXTex.h"

#ifdef _DEBUG
#pragma comment( lib, "lib/Debug/DirectXTex.lib" )
#else
#pragma comment( lib, "lib/Release/DirectXTex.lib" )
#endif


BEGIN_EGEG

// TextureLoader 関数定義
/*===========================================================================*/
// テクスチャのロード
//
// DirectXTexを利用してテクスチャをロードする
// 戻り値はテクスチャのシェーダ―リソースビュー
DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>
TextureLoader::load( const std::wstring& FilePath )
{
    using RetTy = DetailedReturnValue<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
    using namespace DirectX;

    // ファイルからデータを読み込む
    TexMetadata metadata;
    ScratchImage image;
    HRESULT hr = LoadFromWICFile(FilePath.c_str(), 0, &metadata, image);
    if( FAILED(hr) ) { RetTy(false, nullptr, "ファイル読み込みに失敗"); }

    // シェーダ―リソースビューを作成
    ID3D11ShaderResourceView* srv = nullptr;
    hr = CreateShaderResourceViewEx(
        device_.Get(),
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_SHADER_RESOURCE,
        0,
        0,
        false,
        &srv
    );
    if( FAILED(hr) ) { RetTy(false, nullptr, "シェーダ―リソースビューの生成に失敗"); }

    RetTy ret( true, srv );
    srv->Release();
    return ret;
}

END_EGEG
// EOF
